// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/MyBlueprintAsyncActionBase.h"

UMyBlueprintAsyncActionBase* UMyBlueprintAsyncActionBase::AsyncTest(const int ID)
{
	UMyBlueprintAsyncActionBase* NewAsyncTest =NewObject<UMyBlueprintAsyncActionBase>();

	NewAsyncTest->temp = ID;

	return NewAsyncTest;
}

void UMyBlueprintAsyncActionBase::Activate()
{
	onToreta();
}

void UMyBlueprintAsyncActionBase::isEqual()
{	
	
}

void UMyBlueprintAsyncActionBase::onToreta()
{
	if (temp == 1)
	{
		OnSuccess.Broadcast(temp, "Success", temp1);
	}
	else if (temp == 0)
	{
		OnFail.Broadcast(temp, "Fail", temp1);
	}
	else
	{
		OnToreta.Broadcast(temp, "Toreta", temp1);
	}
	RemoveFromRoot();
}
