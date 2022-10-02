// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "MachinePawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponents;
class ACannon;
	UCLASS()
class TANK_API ATankPawn : public AMachinePawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	ATankPawn();
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);

	void SetupCannon(TSubclassOf<ACannon> newCannon);
	void Fire();
	void FireSpecial();
	void AutoFire();
	void ChangeCannon();
	UFUNCTION(BlueprintCallable)
		class UHealthComponent* GetHealthComponent() const  { return HealthComponent; }

	UFUNCTION()
	virtual void TakeDamage(FDamageData DamageData) override;
	
	ACannon* GetCannon() const { return Cannon; }
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComponent;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> EquippedCannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> SecondCannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		class UArrowComponent* CannonSetupPoint;
	
	UPROPERTY()
		ACannon* Cannon;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float MovementSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float RotationSpeed = 100.0f;

	void Die();
	void DamageTaked(float Value);

private:	
	class ATankController* TankController;


	float ForwardMoveAxisValue = 0.0f;
	float RightMoveAxisValue = 0.0f;
	float RotateRightAxisValue = 0.0f;
	float CurrentRightAxisValue = 0.0f;
	float RotateInterpolationKey = 0.1f;
	float TurretInterpolationKey = 0.5f;

};
