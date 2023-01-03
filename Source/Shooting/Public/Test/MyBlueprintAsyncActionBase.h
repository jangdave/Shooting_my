// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MyBlueprintAsyncActionBase.generated.h"

/**
 * 
 */

 DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTTDelegate, int32, ID, FString, Data, int32, isToreta);

UCLASS()
class SHOOTING_API UMyBlueprintAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FTTDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FTTDelegate OnFail;

	UPROPERTY(BlueprintAssignable)
	FTTDelegate OnToreta;

	UPROPERTY()
	int32 temp;

	UPROPERTY()
	int32 temp1;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UMyBlueprintAsyncActionBase* AsyncTest(const int ID);

	virtual void Activate() override;

	void isEqual();

	void onToreta();

};
