

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "GameStructs.h"
#include "Turret.generated.h"

class ACannon;
UCLASS()
class TANK_API ATurret : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	
	ATurret();

	UFUNCTION()
		void TakeDamage(FDamageData DamageData) override;
	
	FVector GetEyesPosition();
	

protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	//virtual void Tick(float DeltaTime) override;
	void Targeting();

	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	void SetupCannon();
	
	void DamageTaked(float Value);
	

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class  UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class UParticleSystem* Particle;
	
	UParticleSystemComponent* Template;

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
		float Accurency = 10.f;

		const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

};
