// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyShootingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UMyShootingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	//static은 남발하면 메모리 관리에 안좋다 꼭 필요한 곳에만 사용
	//쌓아놓으면 내 자산이 된다
	static void MoveMyActor(class AActor* actor, FVector dir, float speed, float deltaTime);

};
