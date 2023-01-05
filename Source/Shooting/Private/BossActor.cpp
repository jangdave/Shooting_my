// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp=CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 300.0f, 150.0f));
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("BossPreset"));

	meshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(1, 6, 3));

}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();
	
	startlocation=GetActorLocation();
}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//현재 위치에서 (0, 0, 200) 위치까지 이동한다
	float distance = (startlocation - GetActorLocation()).Length();
	float shaking = FMath::RandRange(-1.0f,1.0f); 

	if (distance < 500)
	{
		FVector loc = GetActorUpVector()*-1;
		loc.Y = shaking;
		SetActorLocation(GetActorLocation()+loc*100*DeltaTime);
	}
	else
	{
		SetActorLocation(FVector(0,0,200));
	}

	//리니어 이용한 방법-----------------------------------------------
	//testValue += DeltaTime;
	//testValue = FMath::Clamp(testValue, 0.0f, 1.0f);
	//FVector result = FMath::Lerp(startlocation, endlocation, testValue);
	//SetActorLocation(result);
}

