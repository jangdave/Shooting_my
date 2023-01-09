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
//구글검색을 해서 찾아보자

// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//충돌박스 컴포넌트 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	
	//생성된 충돌박스 컨포넌트를 루트 컴포넌트로 설정
	SetRootComponent(boxComp);
	
	//박스 콜리젼의 크기를 가로세로높이 모두 50cm로 설정
	boxComp->SetBoxExtent(FVector(50.0f));

	//박스 콜리젼의 충돌처리프리셋을 "PlayerPreset"으로 설정한다
	boxComp->SetCollisionProfileName(TEXT("PlayerPreset"));

	//메시 컴포넌트 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	//메시 컴포넌트를 루트 컴포넌트 하위 개체로 설정
	meshComp->SetupAttachment(RootComponent);

	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//메시 컴포넌트의 Static Mesh 항목에 큐브 파일을 할당(직접 주소를 입력할 경우 해당 파일을 이동하면 작동안함)
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (cubeMesh.Succeeded())
	{
		//로드한 파일을 메시 컴포넌트의 static mesh 항목에 넣는다
		meshComp->SetStaticMesh(cubeMesh.Object);
	}
}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 컨트롤러를 캐스팅
	APlayerController* PlayerCon = Cast<APlayerController>(GetController());

	if (PlayerCon != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerCon->GetLocalPlayer());

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(imc_myMapping, 0);
		}
	}

	//현재 색상값을 저장한다
	UMaterialInterface* iMat = meshComp->GetMaterial(0);

	FHashedMaterialParameterInfo param = FHashedMaterialParameterInfo(TEXT("param"));
	
	//Material Interface에서 벡터 파라메타값을 initcolor변수에 저장
	iMat->GetVectorParameterValue(param, initColor);
	
	UE_LOG(LogTemp, Warning, TEXT("R: %f, G: %f, B: %f"), initColor.R, initColor.G, initColor.B);

	//Material Interface를 이용해서 Material Instance Dynamic 개체를 만든다
	dynamicMat = UMaterialInstanceDynamic::Create(iMat, this);

	//생성한 다이나믹 메터리얼을 메시에 설정
	if (dynamicMat != nullptr)
	{
		meshComp->SetMaterial(0, dynamicMat);
	}
}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//사용자가 입력한 방향대로 이동
	//벡터의 정규화
	direction.Normalize();
	
	// p = p0 + vt
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;
	// block 일때 true를 하면 미리 탐색을 통해서 찾게함
	SetActorLocation(dir, true);

}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Horizental Axis 입력에 함수를 연결한다
	//PlayerInputComponent->BindAxis("Horizental", this, &APlayerFlight::Horizental);

	//Vertical Axis 입력에 함수를 연결한다
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);

	//Fire 입력에 함수를 연결한다
	//PlayerInputComponent->BindAction("FireBullet", IE_Pressed, this, &APlayerFlight::FireBullet);
	
	//PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &APlayerFlight::FireBullet);

	//블루프린트 + c++버전
	//기존의 UInputComponent*변수를 UEnhancedInputComponent*로 변환
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//함수연결하기
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
	//색상을 레드로 변경
	dynamicMat->SetVectorParameterValue(TEXT("param"), (FVector4)FLinearColor::Red);
	//ChangeHitColor();
	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerFlight::ChangeOriginColor, time, false);
}

//부딪혔을때 색깔을 0.2초동안 바꾸는 함수
//void APlayerFlight::ChangeHitColor()
//{
	//my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor::Red);
	// 위랑 같은거 my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor(255, 0, 0, 255);
//}

void APlayerFlight::ChangeOriginColor()
{
	dynamicMat->SetVectorParameterValue(TEXT("param"), (FVector4)initColor);
	//my_mat->SetVectorParameterValue(TEXT("myColor"), initColor);
	// 위랑 같은거 my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor(255, 0, 0, 255);
}


//블루프린트 + c++버전
// 좌우 입력시 실행되는 함수
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

//블루프린트 + c++버전
// 상하 입력시 실행되는 함수
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

// 마우스 왼쪽을 눌렀을때 실행되는 함수
void APlayerFlight::FireBullet()
{
	//총알을 생성한다
	//총알 블루브린트 변수
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

		//생성된 총알을 각도만큼 일정하게 회전시킨다
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

	//총알발사 효과음 실행
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

//궁극기 폭탄 함수
void APlayerFlight::ExplosionAll()
{
	//모든 에너미 파괴
	//TActorIterator 사용
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

	//TArray<T> 배열을 이용한 방식--------------------------------------------------------------
	//AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());

	//if (gm != nullptr)
	//{
	//	for (int32 i = 0; i < gm->enemies.Num(); i++)
	//	{
			//Pending kill 상태체크
	//		if (IsValid(gm->enemies[i]))
	//		{
	//			gm->enemies[i]->DestoryMySelf();
	//		}
	//	}
		//리스트 초기화
	//	gm->enemies.Empty();
	//}

	//직접만든 델리게이트실행--------------------------------------------------------------------
	//playerBomb.Broadcast();

	dirm.Broadcast(GetActorRightVector());
}

void APlayerFlight::CheckEnemies()
{
	//반경 5미터 이내에 있는 모든 AEnemy엑터들을 감지한다
	//감지된 에너미들의 정보를 담을 변수의 배열
	TArray<FOverlapResult> enemiesInfo;
	FVector centerLoc = GetActorLocation() + GetActorUpVector() * 700;
	FQuat centerRot = GetActorRotation().Quaternion();
	FCollisionObjectQueryParams params = FCollisionObjectQueryParams(ECC_GameTraceChannel2);
	FCollisionShape checkShape = FCollisionShape::MakeSphere(500);

	GetWorld()->OverlapMultiByObjectType(enemiesInfo, centerLoc, centerRot, params, checkShape);

	//체크된 모든 에너미의 이름을 체크한다
	for (FOverlapResult enemyInfo : enemiesInfo)
	{
		UE_LOG(LogTemp,Warning,TEXT("Hited : %s"), *enemyInfo.GetActor()->GetName());
		
		enemyInfo.GetActor()->Destroy();
	}

	DrawDebugSphere(GetWorld(), centerLoc, 500, 20, FColor::Yellow, false, 2);
}