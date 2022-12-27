

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingMyGameMode.h"
#include "MainWidget.h"

void AShootingMyGameMode::BeginPlay()
{
	//위젯 블루프린트 생성
	UMainWidget* Main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	//생성된 위젯을 뷰포트에 그린다
	if (Main_UI != nullptr)
	{
		Main_UI->AddToViewport();

		//현재 점수를 위젯의 curScore 텍스트 블록에 반영 
		Main_UI->PrintCurrentScore();
	}

}

void AShootingMyGameMode::AddScore(int32 count)
{
	currentScore += count;
}
