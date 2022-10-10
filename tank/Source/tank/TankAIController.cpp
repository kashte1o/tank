
#include "TankAIController.h"
#include "TankPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework\Pawn.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!TankPawn)
	
		Initialize();
		
		if (!TankPawn)
			return;

	
	TankPawn->MoveForward(1);

	float rotationValue = GetRotationValue();
	TankPawn->RotateRight(rotationValue);

	Targeting();
}


float ATankAIController::GetRotationValue()
{
	FVector currentPoint = PatrollingPoints[PatrollingIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	float distance = FVector::Distance(currentPoint, pawnLocation);
	//UE_LOG(LogTemp, Warning, TEXT("distance: %f"), distance);
	if (distance <= MovementAccurency)
	{
		PatrollingIndex++;
		if (PatrollingIndex >= PatrollingPoints.Num())
		{
			PatrollingIndex = 0;
		}
	}

	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));

	float rotationValue = 0;
	if (forwardAngle > 5)
		rotationValue = 1;
	if (rightAngle > 90)
		rotationValue = -rotationValue;

	return rotationValue;
}

void ATankAIController::Targeting()
{
	if (!TankPawn)
	{
		return;
	}

	if (IsPlayerInRange() && IsPlayerSeen())
	{
		if (CanFire())
		{
			Fire();
		}
		else
		{
			RotateToPlayer();
		}
	}
}

void ATankAIController::RotateToPlayer()
{
	TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

void ATankAIController::Fire()
{
	TankPawn->Fire();
}

bool ATankAIController::IsPlayerInRange()
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
}

bool ATankAIController::CanFire()
{
	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float AimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return AimAngle <= Accurency;
}

bool ATankAIController::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = TankPawn->GetEyesPosition();

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.bTraceComplex = true;
	params.AddIgnoredActor(TankPawn);
	params.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, params))
	{
		AActor* hitActor = hitResult.GetActor();
		if (hitActor)
		{
			if (hitActor == PlayerPawn)
			{
				DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Red, false, 0.5f, 0, 10.0f);
				return true;
			}
			else
			{
				DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Green, false, 0.5f, 0, 10.0f);
				return false;
			}
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Black, false, 0.5f, 0, 10.0f);
	return false;
}

void ATankAIController::Initialize()
{
	TankPawn = Cast<ATankPawn>(GetPawn());
	if (!TankPawn)
		return;

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector pawnLocation = TankPawn->GetActorLocation();
	MovementAccurency = TankPawn->GetMovementAccurency();
	TArray<FVector> points = TankPawn->GetPatrollingPoints();
	for (FVector point : points)
	{
		PatrollingPoints.Add(point);
	}
	PatrollingIndex = 0;
}