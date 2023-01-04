// Fill out your copyright notice in the Description page of Project Settings.


#include "Enermy.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "PlayerFlight.h"
#include "EngineUtils.h"
#include "ShootingMyGameMode.h"

// Sets default values
AEnermy::AEnermy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collosion"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));
	
	//충돌프리셋 직접 설정하기
	//collision enabled 값을 Query and Physics로 설정
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//응답 채널의 Object type을 Enemy로 설정
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel2);
	//응답 채널을 일괄적으로 ignore처리
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//응답 채널을 Player와 Bullet 채널에 대해서만 오버랩처리
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnermy::BeginPlay()
{
	Super::BeginPlay();

	//추첨을 해서 하나는 정면 방향, 또 다른 하나는 플레이어 방향으로 이동하고 싶다
	//1. 추첨을 한다, 확률은 변수를 이용해서 7:3으로 한다
	int32 drowNumber = FMath::RandRange(1, 100);

	//2. 만일, 뽑은 값이 traceRate보다 작으면
	if (drowNumber <= traceRate)
	{
		//2-1. 레벨에서 플레이어 엑터를 찾는다**********************************************************1번********
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerFlight::StaticClass());

		
		//for문으로도 할수있다 it; => it != nullprt *****************************************************2번********
		for (TActorIterator<APlayerFlight> it(GetWorld()); it; ++it)
		{
			target = *it; 
		}
		if (target != nullptr)
		{
			float temp = target->moveSpeed;
		}
		if (target != nullptr)
		{
			//2-2. 플레이어위치 - 나의 위치 = 갈 방향을 설정
			FVector targetDir = target->GetActorLocation() - GetActorLocation();

			targetDir.Normalize();

			direction = targetDir;
		}
	}
	
	//3. 그렇지 않으면
	else
	{
		//3-1. 정면으로 방향을 정한다
		direction = GetActorForwardVector();
	}
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnermy::OnOverlap);
	boxComp->SetGenerateOverlapEvents(true);

	//게임모드의 enemies 배열에 자기 자신을 넣는다
	AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr)
	{
		gm->enemies.Add(this);
	}
}

// Called every frame
void AEnermy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}

void AEnermy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr)
	{
		player->Destroy();

		//메뉴위젯을 생성하는 함수를 실행한다
		AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());
		if (gm != nullptr)
		{
			gm->ShowMenu();
		}

		//색상 변환
		//player->ReservationHitColor(0.2f);

		Destroy();
	}
		
}

void AEnermy::DestoryMySelf()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_fx, GetActorLocation(), GetActorRotation(), true);
	Destroy();
}

void AEnermy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//자기자신을 배열에서 제거한다.
	AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr)
	{
		gm->enemies.Remove(this);
	}
}
