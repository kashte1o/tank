// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Cannon.h"
#include "Components/ArrowComponent.h"
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
}


void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankController>(GetController());

	SetupCannon(CannonClass);
	
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

	UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue %f, RotateRightAxisValue %f "), CurrentRightAxisValue,  RotateRightAxisValue);
	float yawRotation = CurrentRightAxisValue * RotationSpeed * DeltaTime;
	FRotator currentRotation = GetActorRotation();

	yawRotation = currentRotation.Yaw + yawRotation;
	FRotator newRotation = FRotator(0.0f, yawRotation, 0.0f);
	
	SetActorRotation(newRotation);
	
	
	//TurretRotation

	
		if (TankController)
		{
			FVector MousePos = TankController -> GetMousePos();
			FRotator targetRotaion = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePos);
			FRotator turretRotation = TurretMesh->GetComponentRotation();
			targetRotaion.Pitch = turretRotation.Pitch;
			targetRotaion.Pitch = turretRotation.Roll;
			TurretMesh->SetWorldRotation(FMath::Lerp(targetRotaion, turretRotation, TurretInterpolationKey));

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

