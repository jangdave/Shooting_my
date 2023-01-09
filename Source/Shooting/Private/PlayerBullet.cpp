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
	//���� �ε��� ����� �Ѿ��̶��
	AEnermy* enemy = Cast<AEnermy>(OtherActor);

	if (enemy != nullptr)
	{
		//���� �ִ� ��ġ�� ��������Ʈ ����
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, enemyLoc, enemyRot, true);

		//���� ���� 
		enemy->Destroy();

		//���Ӹ���� ������ 1���� �ø���
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		//���� �Ȱ��� AGameModeBase* gm = GetWorld()->GetAuthGameMode();
		AShootingMyGameMode* myGM = Cast<AShootingMyGameMode>(gm);
		myGM->AddScore(1);
		//UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());

		//�� �ڽŵ� ����
		Destroy();
	}
}