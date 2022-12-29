// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/Gameplaystatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	btn_Resume->OnClicked.AddDynamic(this, &UMenuWidget::ResumeGame);
	btn_Restart->OnClicked.AddDynamic(this, &UMenuWidget::RestartGame);
	btn_Quit->OnClicked.AddDynamic(this, &UMenuWidget::QuitGame);
}

void UMenuWidget::ResumeGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	this->RemoveFromParent();
}

void UMenuWidget::RestartGame()
{
	//������ �ٽ� �ε��Ѵ�
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ShootingMap"));

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	
	//���� ������ �����Ѵ�
	this->RemoveFromParent();

}

void UMenuWidget::QuitGame()
{
	//���� �����Ѵ�
	APlayerController*playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
