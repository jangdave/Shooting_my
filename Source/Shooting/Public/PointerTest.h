// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointerTest.generated.h"

UCLASS()
class SHOOTING_API APointerTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointerTest();

protected:
	//자식 클래스만 접근가능

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//모든 클래스 접근가능

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int32 pt_number = 30;

	float* myAge;
	
private:
	UPROPERTY(EditAnywhere)
	float realAge = 20;



};
