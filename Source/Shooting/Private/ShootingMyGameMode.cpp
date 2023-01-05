

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingMyGameMode.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/Gameplaystatics.h"
#include "EnermySpawner.h"
#include "BossActor.h"
#include "EngineUtils.h"

AShootingMyGameMode::AShootingMyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShootingMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	//���� �������Ʈ ����
	Main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	//������ ������ ����Ʈ�� �׸���
	if (Main_UI != nullptr)
	{
		Main_UI->AddToViewport();

		//�ְ� ������ ���Ϸ� �����Ѵ�
		//FString filePath2 = FString("../../../Content/SaveScore/BestScore.txt");
		
		//�ְ� ������ ���Ͽ��� �о�´�
		FString scoreText;
		bool isLoadSuccess = FFileHelper::LoadFileToString(scoreText, *filePath);
	
		//�о�� ���� bestscore������ �ִ´�
		bestScore = FCString::Atoi(*scoreText);

		//���� ������ ������ curScore �ؽ�Ʈ ��Ͽ� �ݿ� 
		Main_UI->PrintCurrentScore();
	}

	//FString testPath = FPaths::GetProjectFilePath(); ù��°
	//FString testPath = FPaths::ProjectConfigDir()+ TEXT("SaveScore/SaveScore.txt"); �ι�°
	//UE_LOG(LogTemp,Warning,TEXT("test path: %s"), *testPath);

	//��ũ���� �α�����ϱ�
	//GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Emerald, TEXT("logTest"), true);
}

void AShootingMyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShootingMyGameMode::AddScore(int32 count)
{
	currentScore += count;

	//���� ������ ���������� �ְ� �������� ũ�ٸ�
	if (currentScore > bestScore)
	{
		//�ְ� ������ ���������� �ִ´�
		bestScore = currentScore;

		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(bestScore), *filePath);
		UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False"));
	}
	
	if(Main_UI != nullptr)
	{
		//���� ������ ������ curScore �ؽ�Ʈ ��Ͽ� �ݿ�
		Main_UI->PrintCurrentScore();
	}

	if (currentScore >= 30)
	{	
		GetWorld()->GetTimerManager().SetTimer(spawnTimer, this, &AShootingMyGameMode::BossSpawn, 4.0f, false);

		//��� ������ �ߴ�
		StopSpawn();
	}
}

void AShootingMyGameMode::BossSpawn()
{
	GetWorld()->SpawnActor<ABossActor>(bossactor, FVector(0, 0, 700.0f), FRotator::ZeroRotator);
}

void AShootingMyGameMode::StopSpawn()
{
	for (TActorIterator<AEnermySpawner> it(GetWorld()); it; ++it)
	{
		it->SetActorTickEnabled(false);
	}
}

void AShootingMyGameMode::ShowMenu()
{
	//�޴� ������ ȭ�鿡 ǥ���Ѵ�
	menu_UI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if (menu_UI != nullptr)
	{
		menu_UI->AddToViewport();
	}

	//������ �Ͻ����� ���·� �����
	//1. ���� ���� �ð� �帧�� 0���� �����
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	//2. �Ͻ����� �Լ��� ȣ���Ѵ�
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	//���콺 Ŀ�� ���̰� �ϱ�
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}