
#pragma once

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 *
 */
UCLASS()
class TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	void BeginPlay() override;

	UPROPERTY()
		class ATankPawn* TankPawn;

	UPROPERTY()
		APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIParams", meta = (MakeEditWidget = true))
		TArray<FVector> PatrollingPoints;

	int32 PatrollingIndex;
	float MovementAccurency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 10.0f;

	float GetRotationValue();
	void Targeting();
	void RotateToPlayer();
	void Fire();
	bool IsPlayerInRange();
	bool CanFire();
	bool IsPlayerSeen();
	void Initialize();
};
