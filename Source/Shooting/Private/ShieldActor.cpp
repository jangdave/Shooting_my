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

	//�÷��̾�� ���ʹ� ä���ϰ� �浹 ���� ó���ϱ�
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);

	//�浹�� ������ �Լ� ���ε�
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
	//�ε��� ����� �÷��̾���
	player = Cast<APlayerFlight>(OtherActor);
	//�÷��̾�� �����ȴ�
	if (player != nullptr)
	{
		AttachToActor(player, FAttachmentTransformRules::KeepWorldTransform);
		//this->AttachToActor(player, FAttachmentTransformRules::SnapToTargetNotIncludingScale); scale�� ũ�Ⱑ ������� ���ƿ�
		//player->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform); ȸ������

		GetWorld()->GetTimerManager().SetTimer(disTimer, this, &AShieldActor::ResetAttach, 2.0f, false);
	}

	//�ε��� ����� ���ʹ̶��
	AEnermy* enemy = Cast<AEnermy>(OtherActor);
	//�浹�� ���ʹ̸� �ı��Ѵ�
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
	//�ٿ����� �θ� �����Ѵ�.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

