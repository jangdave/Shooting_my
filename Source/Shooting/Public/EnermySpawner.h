// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnermySpawner.generated.h"

UCLASS()
class SHOOTING_API AEnermySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnermySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category=PoolSettings)
	float spawncool = 1;

	UPROPERTY(EditInstanceOnly, Category=PoolSettings)
	TSubclassOf<class AEnermy> enermyFactory;

	UPROPERTY(EditInstanceOnly, Category=PoolSettings)
	class UArrowComponent* spawnArrow;

	UPROPERTY(EditInstanceOnly, Category=PoolSettings)
	class USceneComponent* rootScene;

	bool stop = false;

	void Timer(float time);

private:
	float currentTime = 0;


};
