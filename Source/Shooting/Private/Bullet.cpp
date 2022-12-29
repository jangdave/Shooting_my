// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enermy.h"
#include "ShootingMyGameMode.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�浹���� ����
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 0.5f));
	boxComp->SetCollisionProfileName(TEXT("BulletPreset"));

	//�Ž�����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);

	//�Ž� ��ġ����
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// �浹(������)�� �߻��ϸ� ������ �Լ� ����
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

	// ������ �̺�Ʈ�� �߻��ϵ��� ����
	boxComp->SetGenerateOverlapEvents(true);

	// �¾ �� 2�� �ڿ� �����Ѵ�
	//SetLifeSpan(2.0f);

	// Ÿ�̸��ڵ鷯�� ����
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &ABullet::DestroyMySelf, 2.0f, false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�Ѿ� �����̵�
	// world direction = ��������
	// local direction = �����¿�(������)
	//direction = FVector(1, 0, 0);
	//���� ���� �������� ��� �̵���Ŵ

	direction = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//���� �ε��� ����� �Ѿ��̶��
	AEnermy* enemy = Cast<AEnermy>(OtherActor);

	if (enemy != nullptr)
	{
		//���� �ִ� ��ġ�� ��������Ʈ ����
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, enemyLoc, enemyRot, true);

		//���� ���� 
		enemy->Destroy();

		//���Ӹ���� ������ 1���� �ø���
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		//���� �Ȱ��� AGameModeBase* gm = GetWorld()->GetAuthGameMode();
		AShootingMyGameMode* myGM = Cast<AShootingMyGameMode>(gm);
		myGM->AddScore(1);
		//UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());

		//�� �ڽŵ� ����
		Destroy();
	}
	
}void ABullet::DestroyMySelf()
{
	Destroy();
}

