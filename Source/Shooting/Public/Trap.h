// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class SHOOTING_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//스피어 컴포넌트 충돌체 생성
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=TrapSettings)
	class USphereComponent* sphereComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=TrapSettings)
	class UStaticMeshComponent* meshComp;

	//"InTrap"함수 선언
	UFUNCTION()
	void InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OutTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float currentTime = 0;

	float teleportTime = 1;
};
