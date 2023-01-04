// Fill out your copyright notice in the Description page of Project Settings.


#include "Enermy.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "PlayerFlight.h"
#include "EngineUtils.h"
#include "ShootingMyGameMode.h"

// Sets default values
AEnermy::AEnermy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collosion"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));
	
	//�浹������ ���� �����ϱ�
	//collision enabled ���� Query and Physics�� ����
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//���� ä���� Object type�� Enemy�� ����
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel2);
	//���� ä���� �ϰ������� ignoreó��
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//���� ä���� Player�� Bullet ä�ο� ���ؼ��� ������ó��
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnermy::BeginPlay()
{
	Super::BeginPlay();

	//��÷�� �ؼ� �ϳ��� ���� ����, �� �ٸ� �ϳ��� �÷��̾� �������� �̵��ϰ� �ʹ�
	//1. ��÷�� �Ѵ�, Ȯ���� ������ �̿��ؼ� 7:3���� �Ѵ�
	int32 drowNumber = FMath::RandRange(1, 100);

	//2. ����, ���� ���� traceRate���� ������
	if (drowNumber <= traceRate)
	{
		//2-1. �������� �÷��̾� ���͸� ã�´�**********************************************************1��********
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerFlight::StaticClass());

		
		//for�����ε� �Ҽ��ִ� it; => it != nullprt *****************************************************2��********
		for (TActorIterator<APlayerFlight> it(GetWorld()); it; ++it)
		{
			target = *it; 
		}
		if (target != nullptr)
		{
			float temp = target->moveSpeed;
		}
		if (target != nullptr)
		{
			//2-2. �÷��̾���ġ - ���� ��ġ = �� ������ ����
			FVector targetDir = target->GetActorLocation() - GetActorLocation();

			targetDir.Normalize();

			direction = targetDir;
		}
	}
	
	//3. �׷��� ������
	else
	{
		//3-1. �������� ������ ���Ѵ�
		direction = GetActorForwardVector();
	}
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnermy::OnOverlap);
	boxComp->SetGenerateOverlapEvents(true);

	//���Ӹ���� enemies �迭�� �ڱ� �ڽ��� �ִ´�
	AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr)
	{
		gm->enemies.Add(this);
	}
}

// Called every frame
void AEnermy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}

void AEnermy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr)
	{
		player->Destroy();

		//�޴������� �����ϴ� �Լ��� �����Ѵ�
		AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());
		if (gm != nullptr)
		{
			gm->ShowMenu();
		}

		//���� ��ȯ
		//player->ReservationHitColor(0.2f);

		Destroy();
	}
		
}

void AEnermy::DestoryMySelf()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_fx, GetActorLocation(), GetActorRotation(), true);
	Destroy();
}

void AEnermy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//�ڱ��ڽ��� �迭���� �����Ѵ�.
	AShootingMyGameMode* gm = Cast<AShootingMyGameMode>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr)
	{
		gm->enemies.Remove(this);
	}
}
