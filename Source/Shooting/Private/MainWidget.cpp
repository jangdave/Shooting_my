// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "ShootingMyGameMode.h"
#include "Kismet/Gameplaystatics.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintCurrentScore()
{
	AShootingMyGameMode* myGM = Cast<AShootingMyGameMode>(UGameplayStatics::GetGameMode(this));

	if (myGM != nullptr)
	{
		//현재 점수(정수) -> FText(문자열) 형태로 변환해서 
		FText scoreText = FText::AsNumber(myGM->GetCurrentScore());
		//curScore 텍스트 블록의 값으로 설정한다.
		curScore->SetText(scoreText);

		//현재 점수(정수) -> FText(문자열) 형태로 변환해서 
		FText bestscoreText = FText::AsNumber(myGM->GetBestScore());
		//curScore 텍스트 블록의 값으로 설정한다.
		bestScore->SetText(bestscoreText);
	}
}
