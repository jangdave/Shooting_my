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
		//���� ����(����) -> FText(���ڿ�) ���·� ��ȯ�ؼ� 
		FText scoreText = FText::AsNumber(myGM->GetCurrentScore());
		//curScore �ؽ�Ʈ ����� ������ �����Ѵ�.
		curScore->SetText(scoreText);

		//���� ����(����) -> FText(���ڿ�) ���·� ��ȯ�ؼ� 
		FText bestscoreText = FText::AsNumber(myGM->GetBestScore());
		//curScore �ؽ�Ʈ ����� ������ �����Ѵ�.
		bestScore->SetText(bestscoreText);
	}
}
