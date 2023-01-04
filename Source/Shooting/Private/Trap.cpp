// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"
#include "EngineUtils.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp=CreateDefaultSubobject<USphereComponent>(TEXT("Shpere Collision"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(50);
	meshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

	//오버랩 델리게이트에 intrap함수 연결
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATrap::InTrap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATrap::OutTrap);
	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName(TEXT("TrapPreset"));
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//currentTime이 teleporttime에 도달하면
	currentTime += DeltaTime;

	if (currentTime > teleportTime)
	{
		//랜덤 위치를 설정-------------------------------------------첫번째방법
		//float drowNumber1 = FMath::RandRange(-500.0f,500.0f);
		//float drowNumber2 = FMath::RandRange(-300.0f,300.0f);
		//FVector loc = FVector(0 , drowNumber1, drowNumber2);

		//----------------------------------------------------------두번째방법
		FVector random_vec = FMath::VRand()* 500.0f;
		random_vec.X = 0;

		//그 위치로 이동
		SetActorLocation(random_vec);
				
		//current 초기화
		currentTime = 0;
	}
	//그렇지 않다면
	else
	{
		//시간을 누적
		currentTime += DeltaTime;
	}
}

//"InTrap"함수 구현
void ATrap::InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr)
	{
		//UE_LOG(LogTemp,Warning,TEXT("overlap"));
		player->canFire = false;
	}
}

void ATrap::OutTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr)
	{
		player->canFire = true;
	}
}
