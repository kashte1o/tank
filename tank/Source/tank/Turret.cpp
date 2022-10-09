


#include "Turret.h"

#include <Components\BoxComponent.h>
#include <Components\StaticMeshComponent.h>
#include <Components\ArrowComponent.h>
#include "Engine\StaticMesh.h"
#include "Cannon.h"
#include <Kismet\KismetMathLibrary.h>
#include "HealthComponent.h"
#include <Kismet/GameplayStatics.h>

ATurret::ATurret()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	HitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = HitCollision;

	BodyMesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(HitCollision);
	
	TurretMesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
	{

	BodyMesh->SetStaticMesh(bodyMeshTemp);
	}
	
	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
	{
		TurretMesh->SetStaticMesh(turretMeshTemp);
	}
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::Destroyed);
	HealthComponent->OnHealthChanged.AddUObject(this,&ATurret::DamageTaked);
}

void ATurret::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

FVector ATurret::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	SetupCannon();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(targetingTimerHandle, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);
	
}





void ATurret::Targeting()
{

	if (IsPlayerInRange())
	{
		RotateToPlayer();
	
	if (CanFire())
	{
		Fire();
	}
	}
	
}

void ATurret::Destroyed()
{
	if (Cannon)
	{
		Cannon->Destroyed();

	}
	Destroy();
	Template = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
		FRotator currentRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currentRotation, targetRotation, TargetingSpeed));
}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float AimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return AimAngle <= Accurency;
}

void ATurret::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATurret::SetupCannon()
{
	if (!CannonClass)
	{
		return;
	}

	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);


}


void ATurret::DamageTaked(float Value)
{

	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage: %f, health: %f "), *GetName(), Value, HealthComponent-> GetHealth());


}



