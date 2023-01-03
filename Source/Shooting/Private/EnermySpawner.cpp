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

	//����� �ð��� ����
	currentTime += DeltaTime;
	

	//���� ������ �ð��� ������ ������ �ð����� ũ�ų� ���ٸ�
	if (currentTime >= spawncool)
	{		
		//���ʹ� �������Ʈ ����
		//�ַο� ������Ʈ�� ��ġ�� ȸ�����·� ���缭 ����
		GetWorld()->SpawnActor<AEnermy>(enermyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

		//������ �ð��� �ٽ� 0���� �ʱ�ȭ
		currentTime = 0;
	}

}

