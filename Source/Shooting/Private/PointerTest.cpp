// Fill out your copyright notice in the Description page of Project Settings.


#include "PointerTest.h"

// Sets default values
APointerTest::APointerTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	myAge = &realAge;
	
}

// Called when the game starts or when spawned
void APointerTest::BeginPlay()
{
	Super::BeginPlay();

	//myAge = &realAge;
	//myAge값이 있는 비긴플레이보다 먼저 실행이 안되면 크래쉬날수도있음
	//그럴때는 생성자(위에) 써준다.
	
}

// Called every frame
void APointerTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

