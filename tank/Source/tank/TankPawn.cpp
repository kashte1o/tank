// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Cannon.h"
//#include "Cannon.cpp"
#include "HealthComponent.h"
#include "Components/ArrowComponent.h"
#include <Kismet/GameplayStatics.h>
// Sets default values
ATankPawn::ATankPawn()
{
 
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoxCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankPawn::DamageTaked);

	/*HitEnemy = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitEnemy"));
	HitEnemy->SetAutoActivate(false);
	HitEnemy->SetupAttachment(ProjectileMes);
	*/

	
}


void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotaion = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator turretRotation = TurretMesh->GetComponentRotation();
	targetRotaion.Pitch = turretRotation.Pitch;
	targetRotaion.Pitch = turretRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(targetRotaion, turretRotation, TurretInterpolationKey));




}

FVector ATankPawn::GetEyesPosition() const
{
	return CannonSetupPoint->GetComponentLocation();
}



void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankController>(GetController());

	SetupCannon(EquippedCannonClass);
	
}


void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	FVector currentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector movePosition = currentLocation + ForwardVector * MovementSpeed * ForwardMoveAxisValue * DeltaTime + RightVector * MovementSpeed * RightMoveAxisValue * DeltaTime;
	SetActorLocation(movePosition);
	// BodyRotation
	
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, RotateRightAxisValue, RotateInterpolationKey);

	//UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue %f, RotateRightAxisValue %f "), CurrentRightAxisValue,  RotateRightAxisValue);
	float yawRotation = CurrentRightAxisValue * RotationSpeed * DeltaTime;
	FRotator currentRotation = GetActorRotation();

	yawRotation = currentRotation.Yaw + yawRotation;
	FRotator newRotation = FRotator(0.0f, yawRotation, 0.0f);
	
	SetActorRotation(newRotation);
	
	
	//TurretRotation

	
		if (TankController)
		{
			FVector MousePos = TankController -> GetMousePos();
			RotateTurretTo(MousePos);

		}
	
}

void ATankPawn::MoveForward(float Value)
{
	ForwardMoveAxisValue = Value;
}

void ATankPawn::MoveRight(float Value)
{
	RightMoveAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RotateRightAxisValue = Value;


}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannon)
{

	if (!newCannon)
	{
		return;
	}
	
	if (Cannon)
	{
		Cannon->Destroy();
	}

	
	
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(newCannon, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
}



void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();

	}

}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{

		Cannon->FireSpecial();

	}
}

void ATankPawn::AutoFire()
{
	if (Cannon)
	{

		Cannon->AutoFire();

	}
}

void ATankPawn::ChangeCannon()
{
	TSubclassOf<ACannon> CachedCannon;
	CachedCannon = EquippedCannonClass;
	EquippedCannonClass = SecondCannonClass;
	SecondCannonClass = CachedCannon;
	SetupCannon(EquippedCannonClass);
		



}

void ATankPawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
	

}

void ATankPawn::DamageTaked(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s taked damage: %f, health: %f "), *GetName(), Value, HealthComponent->GetHealth());

}

void ATankPawn::Die()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
	Destroy();
	Template = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
}