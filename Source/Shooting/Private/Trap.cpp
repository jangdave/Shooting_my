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

	//������ ��������Ʈ�� intrap�Լ� ����
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATrap::InTrap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATrap::OutTrap);
	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName(TEXT("TrapPreset"));
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//currentTime�� teleporttime�� �����ϸ�
	currentTime += DeltaTime;

	if (currentTime > teleportTime)
	{
		//���� ��ġ�� ����-------------------------------------------ù��°���
		//float drowNumber1 = FMath::RandRange(-500.0f,500.0f);
		//float drowNumber2 = FMath::RandRange(-300.0f,300.0f);
		//FVector loc = FVector(0 , drowNumber1, drowNumber2);

		//----------------------------------------------------------�ι�°���
		FVector random_vec = FMath::VRand()* 500.0f;
		random_vec.X = 0;

		//�� ��ġ�� �̵�
		SetActorLocation(random_vec);
				
		//current �ʱ�ȭ
		currentTime = 0;
	}
	//�׷��� �ʴٸ�
	else
	{
		//�ð��� ����
		currentTime += DeltaTime;
	}
}

//"InTrap"�Լ� ����
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
