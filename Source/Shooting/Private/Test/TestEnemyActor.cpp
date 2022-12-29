// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestEnemyActor.h"

// Sets default values
ATestEnemyActor::ATestEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	meshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	

}

// Called when the game starts or when spawned
void ATestEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	//���� ã�´�

	//���� ����(������ġ - ������ġ)�� ���� ����
	
	//�ƴ϶�� �������� ����	
	
}

// Called every frame
void ATestEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

