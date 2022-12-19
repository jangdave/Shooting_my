// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeTest.generated.h"

UCLASS()
class SHOOTING_API ACodeTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACodeTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CodeVariable)
		int32 number;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CodeVariable) int32 number;까지 한 문장
	//EditAnywhere, DefaultsOnly, InstanceOnly

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CodeVariable)
		int32 number2;


	// 실수형 변수 fnumber를 선언한다.
	float fnumber2 = 3.14f;
	float fnumber1;

	// 문자형 변수 name을 선언한다.
	FString name1;
	FString name2 = FString(TEXT("박원석"));
	//TEXT("박원석") = L"박원석"

	// 	UPROPERTY(EditAnywhere, Category = CodeVariable)
	// 	FString myname = TEXT("윤기");
	// 	UPROPERTY(EditAnywhere, Category = CodeVariable)
	// 	FString firstname = TEXT("장");

	UFUNCTION(BlueprintPure)
		//BlueprintCallable

		FString StringAppender(FString myname, FString firstname);

	// 논리형 변수 isStudent를 선언한다.
	bool isStudent;
	// bool isStudent = false;
	bool isTeacher = true;

	int32 Add(int32 num1, int32 num2);

	int32 Subtract(int32 num1, int32 num2);

	int32 Divide(int32 num1, int32 num2);

	int32 Multifly(int32 num1, int32 num2);

	float divide(int num1, int num2);

	int32 result = 100;

	// 	UPROPERTY(EditAnywhere, Category = CodeVariable)
	// 	int32 age = 25;
	// 	UPROPERTY(EditAnywhere, Category = CodeVariable)
	// 	int32 height = 170;
	// 	UPROPERTY(EditAnywhere, Category = CodeVariable)
	// 	FString Nation;
	
	int32 checker = 123;

	void Gugudan(int32 gugunum);

};