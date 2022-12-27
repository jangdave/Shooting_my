

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingMyGameMode.h"
#include "MainWidget.h"

void AShootingMyGameMode::BeginPlay()
{
	//���� �������Ʈ ����
	UMainWidget* Main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	//������ ������ ����Ʈ�� �׸���
	if (Main_UI != nullptr)
	{
		Main_UI->AddToViewport();

		//���� ������ ������ curScore �ؽ�Ʈ ��Ͽ� �ݿ� 
		Main_UI->PrintCurrentScore();
	}

}

void AShootingMyGameMode::AddScore(int32 count)
{
	currentScore += count;
}
