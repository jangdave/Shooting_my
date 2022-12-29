

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingMyGameMode.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/Gameplaystatics.h"

void AShootingMyGameMode::BeginPlay()
{
	//위젯 블루프린트 생성
	Main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	//생성된 위젯을 뷰포트에 그린다
	if (Main_UI != nullptr)
	{
		Main_UI->AddToViewport();

		//최고 점수를 파일로 저장한다
		//FString filePath2 = FString("../../../Content/SaveScore/BestScore.txt");
		
		//최고 점수를 파일에서 읽어온다
		FString scoreText;
		bool isLoadSuccess = FFileHelper::LoadFileToString(scoreText, *filePath);
	
		//읽어온 값을 bestscore변수에 넣는다
		bestScore = FCString::Atoi(*scoreText);

		//현재 점수를 위젯의 curScore 텍스트 블록에 반영 
		Main_UI->PrintCurrentScore();
	}

	//FString testPath = FPaths::GetProjectFilePath(); 첫번째
	//FString testPath = FPaths::ProjectConfigDir()+ TEXT("SaveScore/SaveScore.txt"); 두번째
	//UE_LOG(LogTemp,Warning,TEXT("test path: %s"), *testPath);

	//스크린에 로그출력하기
	//GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Emerald, TEXT("logTest"), true);
}

void AShootingMyGameMode::AddScore(int32 count)
{
	currentScore += count;

	//만일 누적된 현재점수가 최고 점수보다 크다면
	if (currentScore > bestScore)
	{
		//최고 점수에 현재점수를 넣는다
		bestScore = currentScore;

		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(bestScore), *filePath);
		UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False"));
	}
	
	if(Main_UI != nullptr)
	{
		//현재 점수를 위젯의 curScore 텍스트 블록에 반영
		Main_UI->PrintCurrentScore();
	}
}

void AShootingMyGameMode::ShowMenu()
{
	//메뉴 위젯을 화면에 표시한다
	menu_UI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if (menu_UI != nullptr)
	{
		menu_UI->AddToViewport();
	}

	//게임을 일시정지 상태로 만든다
	//1. 직접 게임 시간 흐름을 0으로 만든다
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	//2. 일시정지 함수를 호출한다
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	//마우스 커서 보이게 하기
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}