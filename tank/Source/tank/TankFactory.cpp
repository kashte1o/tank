


#include "TankFactory.h"
#include "MapLoader.h"
#include "Components\StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components\BoxComponent.h"
#include "Components\ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"
#include "HealthComponent.h"
#include "Components/AudioComponent.h"

ATankFactory::ATankFactory()
{
 	
	PrimaryActorTick.bCanEverTick = false;


	USceneComponent* SceneComp =  CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneComp);

	//DestroyedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestroyedMesh"));
	//DestroyedMesh->SetupAttachment(SceneComp);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TankSpawnPoint"));
	TankSpawnPoint->SetupAttachment(BuildingMesh);

	HealthComponent =CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankFactory::DamageTaked);
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
	
	SpawnSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotSound"));
	SpawnSound->SetAutoActivate(false);
}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();
	
	if (MapLoader)
	{
		MapLoader->SetIsActivated(false);
	}
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this,&ATankFactory::SpawnTank, SpawnTankRate, true, SpawnTankRate);
	
	FTimerHandle SpawnTimer;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ATankFactory::SpawnTank, SpawnTankRate, true, 2.0f);
		

}

void ATankFactory::SpawnTank()
{
	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()-> SpawnActorDeferred<ATankPawn>(SpawnTankClass,spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	newTank->SetPatrollingPoints(TankWayPoints);
	//
	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
	
	
	SpawnSound->Play();
}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);

}

void ATankFactory::Die()
{
	if (MapLoader)
	{
		MapLoader->SetIsActivated(true);
	}

	Destroy();
	
	
	
	TemplateParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage: %f, health: %f "), *GetName(), DamageValue, HealthComponent->GetHealth());
}






