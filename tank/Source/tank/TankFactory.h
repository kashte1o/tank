// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include <Engine/TargetPoint.h>
#include "TankPawn.h"
//#include "MapLoader.h"
#include "TankFactory.generated.h"


UCLASS()
class TANK_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	
	ATankFactory();
	UFUNCTION()
		virtual void TakeDamage(FDamageData DamageData) override;
	
	UFUNCTION()
		virtual void BeginPlay() override;

protected:
	

	void SpawnTank();

	
	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* BuildingMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* DestroyedMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollider;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* TankSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
		TSubclassOf <ATankPawn> SpawnTankClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
		float SpawnTankRate = 2.0f;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
		class AMapLoader* MapLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
		TArray<ATargetPoint*> TankWayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UParticleSystem* Particle;
	
	UParticleSystemComponent* TemplateParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		class UAudioComponent* SpawnSound;

	
	
};
