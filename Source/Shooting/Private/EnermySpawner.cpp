// Fill out your copyright notice in the Description page of Project Settings.


#include "EnermySpawner.h"
#include "Enermy.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AEnermySpawner::AEnermySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(rootScene);
	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Arrow"));
	spawnArrow->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnermySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnermySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//경과된 시간을 누적
	currentTime += DeltaTime;
	

	//만일 누적된 시간이 스폰쿨에 지정한 시간보다 크거나 같다면
	if (currentTime >= spawncool)
	{		
		//에너미 블루프린트 생성
		//애로우 컴포넌트의 위치와 회전상태로 맞춰서 생성
		GetWorld()->SpawnActor<AEnermy>(enermyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

		//누적된 시간을 다시 0으로 초기화
		currentTime = 0;
	}

}

