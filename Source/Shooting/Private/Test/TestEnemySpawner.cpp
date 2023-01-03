// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestEnemySpawner.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"




// Sets default values
ATestEnemySpawner::ATestEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComp=CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(sceneComp);
	arrowComp=CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Comp"));
	arrowComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	if (currentTime >= spawnTime)
	{
		GetWorld()->SpawnActor<ATestEnemyActor>(factory, arrowComp->GetComponentLocation(), arrowComp->GetComponentRotation());
		currentTime = 0;
	}
	
}

