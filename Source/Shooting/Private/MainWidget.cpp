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
		FText scoreText = FText::AsNumber(myGM->GetCurrentScore());
		//���� ����(����) -> FText(���ڿ�) ���·� ��ȯ�ؼ� curScore �ؽ�Ʈ ����� ������ �����Ѵ�.
		curScore->SetText(scoreText);
	}
}
