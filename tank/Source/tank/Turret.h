

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.h"
#include "Turret.generated.h"

class ACannon;
UCLASS()
class TANK_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATurret();

	virtual void Tick(float DeltaTime) override;
	void Targeting();
	
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	void SetupCannon();

protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* BodyMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class UBoxComponent* HitCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		TSubclassOf<ACannon> CannonClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class  UArrowComponent* CannonSetupPoint;


	UPROPERTY()
		ACannon* Cannon;

	UPROPERTY()
		APawn* PlayerPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
		
		float TargetingRange = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
		
		float TargetingSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
		
		float TargetingRate = 0.005f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
		float Accurency = 10;

		const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

};
