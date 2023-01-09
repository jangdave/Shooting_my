// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/BoxComponent.h"
#include "Enermy.h"
#include "ShootingMyGameMode.h"
#include "Kismet/GameplayStatics.h"

APlayerBullet::APlayerBullet()
{
	boxComp->SetCollisionProfileName(TEXT("BulletPreset"));
}

void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	SetDirection(GetActorForwardVector());

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnOverlap);
}

void APlayerBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//만일 부딪힌 대상이 총알이라면
	AEnermy* enemy = Cast<AEnermy>(OtherActor);

	if (enemy != nullptr)
	{
		//적이 있던 위치에 폭발이펙트 생성
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, enemyLoc, enemyRot, true);

		//적을 제거 
		enemy->Destroy();

		//게임모드의 점수를 1점씩 올린다
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		//위랑 똑같다 AGameModeBase* gm = GetWorld()->GetAuthGameMode();
		AShootingMyGameMode* myGM = Cast<AShootingMyGameMode>(gm);
		myGM->AddScore(1);
		//UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());

		//나 자신도 제거
		Destroy();
	}
}