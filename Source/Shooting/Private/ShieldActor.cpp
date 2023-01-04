// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enermy.h"
#include "PlayerFlight.h"
#include "ShootingMyGameMode.h"
#include "Kismet/Gameplaystatics.h"

// Sets default values
AShieldActor::AShieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(20.0f,100.0f,30.0f));
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShieldActor::BeginPlay()
{
	Super::BeginPlay();

	//플레이어랑 에너미 채널하고만 충돌 응답 처리하기
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);

	//충돌시 실행할 함수 바인딩
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AShieldActor::ShieldOnOverlapped);
	boxComp->SetGenerateOverlapEvents(true);
}

// Called every frame
void AShieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShieldActor::ShieldOnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//부딪힌 대상이 플레이어라면
	player = Cast<APlayerFlight>(OtherActor);
	//플레이어에게 부착된다
	if (player != nullptr)
	{
		AttachToActor(player, FAttachmentTransformRules::KeepWorldTransform);
		//this->AttachToActor(player, FAttachmentTransformRules::SnapToTargetNotIncludingScale); scale의 크기가 원래대로 돌아옴
		//player->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform); 회전발판

		GetWorld()->GetTimerManager().SetTimer(disTimer, this, &AShieldActor::ResetAttach, 2.0f, false);
	}

	//부딪힌 대상이 에너미라면
	AEnermy* enemy = Cast<AEnermy>(OtherActor);
	//충돌한 에너미를 파괴한다
	if (enemy != nullptr)
	{
		enemy->Destroy();

		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AShootingMyGameMode* myGM = Cast<AShootingMyGameMode>(gm);
		myGM->AddScore(1);
	}
}

void AShieldActor::ResetAttach()
{
	//붙여놨던 부모를 해제한다.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

