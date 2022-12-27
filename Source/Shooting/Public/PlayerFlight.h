// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerFlight.generated.h"

UCLASS()
class SHOOTING_API APlayerFlight : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerFlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerSettings)
	float moveSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerSettings)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	class UInputAction* ia_Horizental;

	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	class UInputAction* ia_Vertical;

	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	class UInputAction* ia_FireBullet;

	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	class UInputMappingContext* imc_myMapping;

	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	class USoundBase* fireSound;

	void ReservationHitColor(float time);

	//void ChangeHitColor();
	
	void ChangeOriginColor();


private:
	
	//엔진안 요소랑 똑같지 않아도 되긴함
	//UFUNCTION(BlueprintCallable)
	//void Horizental(float val);

	UFUNCTION(BlueprintCallable)
	void Horizental(const FInputActionValue& value);

	//UFUNCTION(BlueprintCallable)
	//void Vertical(float val);

	UFUNCTION(BlueprintCallable)
	void Vertical(const FInputActionValue& value);

	//총알발사 함수
	//UFUNCTION(BlueprintCallable)
	//void FireBullet();
	
	UFUNCTION(BlueprintCallable)
	void FireBullet();
	
	float H;
	float V;

	FVector direction;
	FLinearColor initColor;
	FTimerHandle colorTimer;
	UMaterialInstanceDynamic* dynamicMat;
};
