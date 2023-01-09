// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBullet.h"
#include "Kismet/KismetMathLibrary.h"

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
	//float distance = (startlocation - GetActorLocation()).Length();
	//float shaking = FMath::RandRange(-1.0f,1.0f); 

	//if (distance < 500)
	//{
	//	FVector loc = GetActorUpVector()*-1;
	//	loc.Y = shaking;
	//	SetActorLocation(GetActorLocation()+loc*100*DeltaTime);
	//}
	//else
	//{
	//	SetActorLocation(FVector(0,0,200));
	//}

	//리니어 이용한 방법-----------------------------------------------
	testValue += DeltaTime;
	testValue = FMath::Clamp(testValue, 0.0f, 1.0f);
	FVector result = FMath::Lerp(startlocation, endlocation, testValue);
	SetActorLocation(result);

	if (currentTime > pattern_delay)
	{
		BossAttack1(15, 6);
		currentTime = 0;
	}
	else
	{
		currentTime += DeltaTime;
	}
}

void ABossActor::BossAttack1(float angle, int32 count)
{
	float tangle = 270 - angle * (count - 1) * 0.5f;
	
	for(int32 i = 0; i < count; i++)
	{	
		//기본 좌표 (0, rcos@, rsin@)
		FVector bullet_base = FVector(0, 
					100 * FMath::Cos(FMath::DegreesToRadians (tangle + angle*i)), 
					100 * FMath::Sin(FMath::DegreesToRadians (tangle + angle*i)));
		
		//AEnemyBullet* enemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(bullet, 
		//			GetActorLocation() + bullet_base, FRotator::ZeroRotator);
		
		//enemyBullet->SetDirection(bullet_base.GetSafeNormal());

		//---------------------------------------------------------------------------------
		//UP벡터 축을 bullet_base 방향으로 회전시켰을때의 로테이터 값을 계산한다
		AEnemyBullet* enemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(bullet, 
					GetActorLocation() + bullet_base, FRotator(-90, 0, 0));

		FRotator rot = UKismetMathLibrary::MakeRotFromZX(enemyBullet->GetActorUpVector(), bullet_base.GetSafeNormal());

		enemyBullet->SetActorRotation(rot);
	}
}

