// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTest.h"
#pragma warning (disable : 4458) //c4458 경고끄기

// Sets default values
ACodeTest::ACodeTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeTest::BeginPlay()
{
	Super::BeginPlay();

	//Add 함수에 입력값 8,4를 넣어서 결과를 result 변수에 받는다.
	//int32 result1 = Add(8, 4);
	//int32 result2 = Subtract(8, 4);
	//int32 result3 = Divide(8, 4);
	//int32 result4 = Multifly(8, 4);
	//float result5 = divide(8, 4);

	//result 변수에 있는 값을 화면에 출력한다.
	//UE_LOG(LogTemp, Warning, TEXT("Result1 : %d"), result1);
	//UE_LOG(LogTemp, Warning, TEXT("Result2 : %d"), result2);
	//UE_LOG(LogTemp, Warning, TEXT("Result3 : %d"), result3);
	//UE_LOG(LogTemp, Warning, TEXT("Result4 : %d"), result4);
	//UE_LOG(LogTemp, Warning, TEXT("Result5 : %.1f"), result5);


	//number = 3;
	//number2 = number;
	//number2 = 7;



	// 	UE_LOG(LogTemp, Warning, TEXT("%d"), number2);
	// 	UE_LOG(LogTemp, Warning, TEXT("%.0f"), fnumber2);
	// 	UE_LOG(LogTemp, Warning, TEXT("Hello World! is %s"),*name2);

	// 	if (isTeacher == true)
 	//{
 	//UE_LOG(LogTemp, Warning, TEXT("true"));
 	//}
 	//else
 	//{
 	//UE_LOG(LogTemp, Warning, TEXT("false"));
 	//}



	// 만일 나이가 30살 이상이면 꼰대라고 출력
	/*if (age >= 30)
	{
		UE_LOG(LogTemp, Warning, TEXT("꼰대"));
	}
	else if(age >= 20)
	{
		UE_LOG(LogTemp, Warning, TEXT("꼰대아님"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Z세대"));
	}*/


	//만일 나이가 20살 이상이면서 키가 160 이상인 경우에는 "환영" 출력
	//아니라면 "외면" 출력

	/*if (age >= 20 || height >= 160)
	{
		UE_LOG(LogTemp, Warning, TEXT("환영"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("외면"));
	}*/

	/*if ((Nation == TEXT("한국")) && (age >= 20) && (age < 40))
	{
		UE_LOG(LogTemp, Warning, TEXT("청년"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("청년아님"));
	}*/
	
	//FString result = firstname + myname;

	//FString FullName = StringAppender(TEXT("윤기"), TEXT("장"));

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FullName);
	
	
	// 	if (checker/2 == 0)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("even"));
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("odd"));
	// 	}

	//for문 
	//for(초기화;조건식;증감식)
	//{
	//	to do
	//}

	//"안녕하세요" 10번 반복 출력
	// 	for (int32 i = 0; i < 10; i++)
	// 	{
	// 		if (i <= 3)
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("안녕하세요."));
	// 		}
	// 		else if (i<=6)
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("고맙습니다."));
	// 		}
	// 		else
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("잘가세요."));
	// 		}
	// 	}

	// 	int32 num = 3;
	// 
	// 	num = num + 2;
	//num += 2;
	//num -= 2;
	//i = i - 1; == i

	//num++ 계산하고 1증가
	//++num 1증가 시키고 계산

	// 	int32 temp = 2;
	// 	int32 sum = temp + num++;
	
	//for(int32 i = 1; i <= 9; i++)
	//{
	//	int32 multiply = i * 7;
	//	UE_LOG(LogTemp, Warning, TEXT("%d*%d=%d"), 7, i, multiply);
	//}
	

	/*for (int32 i = 2; i <= 9; i++)
	{
		for (int32 j = 1; j <= 9; j++)
		{
			int32 sum = i * j;
			UE_LOG(LogTemp, Warning, TEXT("%d*%d=%d"), i, j, sum);
		}
		UE_LOG(LogTemp, Warning, TEXT("=============="));
	}*/

	Gugudan(7);

	UE_LOG(LogTemp, Warning, TEXT("%d"),Add(3,1));

}


void ACodeTest::Gugudan(int32 gugunum)
{
	for (int32 j = 1; j <= 9; j++)
	{
		int32 sum = gugunum * j;
		UE_LOG(LogTemp, Warning, TEXT("%d*%d=%d"), gugunum, j, sum);
	}
	UE_LOG(LogTemp, Warning, TEXT("=============="));
}

// Called every frame
void ACodeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


int32 ACodeTest::Add(int32 num1, int32 num2)
{
	// to do
	int32 result = num1 + num2;
	return result;
}

int32 ACodeTest::Subtract(int32 num1, int32 num2)
{
	return num1 - num2;
}


int32 ACodeTest::Divide(int32 num1, int32 num2)
{
	return num1 / num2;
}

int32 ACodeTest::Multifly(int32 num1, int32 num2)
{
	return num1 * num2;
}

float ACodeTest::divide(int num1, int num2)
{
	return (float)num2 / (float)num1;
	// float(num2)도 가능
}

FString ACodeTest::StringAppender(FString myname, FString firstname)
{
	return firstname + myname;
}


//전역변수 & 지역변수
//Header파일에 선언한 변수,함수 바깥쪽 && 클래스 안쪽 => 전역변수 (여러함수에 쓰임, 항상 변수가 유지되어야하는 경우 ex 체력,목숨)
//함수 안에 선언한 변수 => 지역변수