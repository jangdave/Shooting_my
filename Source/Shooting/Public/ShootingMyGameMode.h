// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingMyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AShootingMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UMainWidget> mainWidget;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UMenuWidget> menuWidget;

	TArray<class AEnermy*> enemies;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentScore() { return currentScore; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetBestScore() { return bestScore; }

	void ShowMenu();

	virtual void BeginPlay() override;

	void AddScore(int32 count);

private:
	int32 currentScore = 0;

	int32 bestScore = 0;

	class UMainWidget* Main_UI;

	class UMenuWidget* menu_UI;

	FString filePath = FString("D:/unreal/Shooting_my/Content/SaveScore/BestScore.txt");
	
	FString filePath2 = FString("../../../Content/SaveScore/BestScore.txt");
};
