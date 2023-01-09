// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enermy.h"
#include "EngineUtils.h"
#include "ShootingMyGameMode.h"
#include "DrawDebugHelpers.h"
//���۰˻��� �ؼ� ã�ƺ���

// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�浹�ڽ� ������Ʈ ����
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	
	//������ �浹�ڽ� ������Ʈ�� ��Ʈ ������Ʈ�� ����
	SetRootComponent(boxComp);
	
	//�ڽ� �ݸ����� ũ�⸦ ���μ��γ��� ��� 50cm�� ����
	boxComp->SetBoxExtent(FVector(50.0f));

	//�ڽ� �ݸ����� �浹ó���������� "PlayerPreset"���� �����Ѵ�
	boxComp->SetCollisionProfileName(TEXT("PlayerPreset"));

	//�޽� ������Ʈ ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	//�޽� ������Ʈ�� ��Ʈ ������Ʈ ���� ��ü�� ����
	meshComp->SetupAttachment(RootComponent);

	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//�޽� ������Ʈ�� Static Mesh �׸� ť�� ������ �Ҵ�(���� �ּҸ� �Է��� ��� �ش� ������ �̵��ϸ� �۵�����)
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (cubeMesh.Succeeded())
	{
		//�ε��� ������ �޽� ������Ʈ�� static mesh �׸� �ִ´�
		meshComp->SetStaticMesh(cubeMesh.Object);
	}
}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();

	//�÷��̾� ��Ʈ�ѷ��� ĳ����
	APlayerController* PlayerCon = Cast<APlayerController>(GetController());

	if (PlayerCon != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerCon->GetLocalPlayer());

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(imc_myMapping, 0);
		}
	}

	//���� ������ �����Ѵ�
	UMaterialInterface* iMat = meshComp->GetMaterial(0);

	FHashedMaterialParameterInfo param = FHashedMaterialParameterInfo(TEXT("param"));
	
	//Material Interface���� ���� �Ķ��Ÿ���� initcolor������ ����
	iMat->GetVectorParameterValue(param, initColor);
	
	UE_LOG(LogTemp, Warning, TEXT("R: %f, G: %f, B: %f"), initColor.R, initColor.G, initColor.B);

	//Material Interface�� �̿��ؼ� Material Instance Dynamic ��ü�� �����
	dynamicMat = UMaterialInstanceDynamic::Create(iMat, this);

	//������ ���̳��� ���͸����� �޽ÿ� ����
	if (dynamicMat != nullptr)
	{
		meshComp->SetMaterial(0, dynamicMat);
	}
}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//����ڰ� �Է��� ������ �̵�
	//������ ����ȭ
	direction.Normalize();
	
	// p = p0 + vt
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;
	// block �϶� true�� �ϸ� �̸� Ž���� ���ؼ� ã����
	SetActorLocation(dir, true);

}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Horizental Axis �Է¿� �Լ��� �����Ѵ�
	//PlayerInputComponent->BindAxis("Horizental", this, &APlayerFlight::Horizental);

	//Vertical Axis �Է¿� �Լ��� �����Ѵ�
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);

	//Fire �Է¿� �Լ��� �����Ѵ�
	//PlayerInputComponent->BindAction("FireBullet", IE_Pressed, this, &APlayerFlight::FireBullet);
	
	//PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &APlayerFlight::FireBullet);

	//�������Ʈ + c++����
	//������ UInputComponent*������ UEnhancedInputComponent*�� ��ȯ
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//�Լ������ϱ�
	enhancedInputComponent->BindAction(ia_Horizental, ETriggerEvent::Triggered, this, &APlayerFlight::Horizental);
	enhancedInputComponent->BindAction(ia_Horizental, ETriggerEvent::Completed, this, &APlayerFlight::Horizental);
	
	enhancedInputComponent->BindAction(ia_Vertical, ETriggerEvent::Triggered, this, &APlayerFlight::Vertical);
	enhancedInputComponent->BindAction(ia_Vertical, ETriggerEvent::Completed, this, &APlayerFlight::Vertical);

	enhancedInputComponent->BindAction(ia_FireBullet, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);
	enhancedInputComponent->BindAction(ia_Boost, ETriggerEvent::Triggered, this, &APlayerFlight::Boost);
	//enhancedInputComponent->BindAction(ia_Boost, ETriggerEvent::Completed, this, &APlayerFlight::Boost);
	//enhancedInputComponent->BindAction(ia_UnBoost, ETriggerEvent::Completed, this, &APlayerFlight::UnBoost);
	enhancedInputComponent->BindAction(ia_Boom, ETriggerEvent::Triggered, this, &APlayerFlight::CheckEnemies);
			
}

void APlayerFlight::ReservationHitColor(float time)
{
	//������ ����� ����
	dynamicMat->SetVectorParameterValue(TEXT("param"), (FVector4)FLinearColor::Red);
	//ChangeHitColor();
	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerFlight::ChangeOriginColor, time, false);
}

//�ε������� ������ 0.2�ʵ��� �ٲٴ� �Լ�
//void APlayerFlight::ChangeHitColor()
//{
	//my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor::Red);
	// ���� ������ my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor(255, 0, 0, 255);
//}

void APlayerFlight::ChangeOriginColor()
{
	dynamicMat->SetVectorParameterValue(TEXT("param"), (FVector4)initColor);
	//my_mat->SetVectorParameterValue(TEXT("myColor"), initColor);
	// ���� ������ my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor(255, 0, 0, 255);
}


//�������Ʈ + c++����
// �¿� �Է½� ����Ǵ� �Լ�
//void APlayerFlight::Horizental(float value)
//{
//	H = value;
	//UE_LOG(LogTemp, Warning, TEXT("H : %.4f"), H);
//	direction.Y = H;
//}


void APlayerFlight::Horizental(const FInputActionValue& value)
{
	H = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("H : %.4f"), H);
	direction.Y = H;
}

//�������Ʈ + c++����
// ���� �Է½� ����Ǵ� �Լ�
//void APlayerFlight::Vertical(float value)
//{
//	V = value;
	//UE_LOG(LogTemp, Warning, TEXT("V : %.4f"), V);
//	direction.Z = V;
//}

void APlayerFlight::Vertical(const FInputActionValue& value)
{
	V = value.Get<float>();
	direction.Z = V;
}

// ���콺 ������ �������� ����Ǵ� �Լ�
void APlayerFlight::FireBullet()
{
	//�Ѿ��� �����Ѵ�
	//�Ѿ� ���기Ʈ ����
	//FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 100.0f;
	//FRotator spawnRotation = FRotator(90.0f, 0, 0);
	if(canFire != true)
	{
		return;
	}
	for (int32 i = 0; i < bulletCount; i++)
	{	
		float len = (bulletCount-1)* bulletSpacing;
		float y = len * -0.5f;
		FVector set = FVector(0, y + bulletSpacing * i, 0); 
		FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 100.0f;
		spawnPosition += set;
		FRotator spawnRotation = FRotator(90.0f, 0, 0);
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation, param);

		//������ �Ѿ��� ������ŭ �����ϰ� ȸ����Ų��
		if(bullet != nullptr && IsValid(bullet))
		{
			float yaw = (bulletCount-1) * bulletAngle * -0.5f;
			FRotator ang = FRotator(0, 0, yaw + bulletAngle * i);
			bullet->AddActorWorldRotation(ang);
		}
	}
	//FActorSpawnParameters param;
	//param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation, param);

	//�Ѿ˹߻� ȿ���� ����
	UGameplayStatics::PlaySound2D(this, fireSound);
}

void APlayerFlight::Boost()
{	
	isBool = !isBool;
	if (isBool)
	{
		moveSpeed = moveSpeedOrigin*2;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Boost"));
		moveSpeed = moveSpeedOrigin;	
	}
}

void APlayerFlight::UnBoost()
{
	//UE_LOG(LogTemp,Warning,TEXT("UnBoost"));
	//moveSpeed = moveSpeedOrigin;
}

//�ñر� ��ź �Լ�
void APlayerFlight::ExplosionAll()
{
	//��� ���ʹ� �ı�
	//TActorIterator ���
	//for (TActorIterator<AEnermy> it(GetWorld()); it; ++it)
	//{
	//	target = *it;
		
	//	if (target != nullptr)
	//	{
	//		target->DestoryMySelf();
	//	}
	//	else
	//	{
	//		return;
	//	}
	//}

	//TArray<T> �迭�� �̿��� ���--------------------------------------------------------------
	//AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());

	//if (gm != nullptr)
	//{
	//	for (int32 i = 0; i < gm->enemies.Num(); i++)
	//	{
			//Pending kill ����üũ
	//		if (IsValid(gm->enemies[i]))
	//		{
	//			gm->enemies[i]->DestoryMySelf();
	//		}
	//	}
		//����Ʈ �ʱ�ȭ
	//	gm->enemies.Empty();
	//}

	//�������� ��������Ʈ����--------------------------------------------------------------------
	//playerBomb.Broadcast();

	dirm.Broadcast(GetActorRightVector());
}

void APlayerFlight::CheckEnemies()
{
	//�ݰ� 5���� �̳��� �ִ� ��� AEnemy���͵��� �����Ѵ�
	//������ ���ʹ̵��� ������ ���� ������ �迭
	TArray<FOverlapResult> enemiesInfo;
	FVector centerLoc = GetActorLocation() + GetActorUpVector() * 700;
	FQuat centerRot = GetActorRotation().Quaternion();
	FCollisionObjectQueryParams params = FCollisionObjectQueryParams(ECC_GameTraceChannel2);
	FCollisionShape checkShape = FCollisionShape::MakeSphere(500);

	GetWorld()->OverlapMultiByObjectType(enemiesInfo, centerLoc, centerRot, params, checkShape);

	//üũ�� ��� ���ʹ��� �̸��� üũ�Ѵ�
	for (FOverlapResult enemyInfo : enemiesInfo)
	{
		UE_LOG(LogTemp,Warning,TEXT("Hited : %s"), *enemyInfo.GetActor()->GetName());
		
		enemyInfo.GetActor()->Destroy();
	}

	DrawDebugSphere(GetWorld(), centerLoc, 500, 20, FColor::Yellow, false, 2);
}