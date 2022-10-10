// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/PointLightComponent.h>
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapLoader.generated.h"

UCLASS()
class TANK_API AMapLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMapLoader();
	void SetIsActivated(bool NewIsActivated);
	void SetActivatedLights();
	virtual void BeginPlay() override;

protected:
	

	UFUNCTION()
		void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor*OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* BuildingMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UPointLightComponent* ActivatedLight;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UPointLightComponent* DeactivatedLight;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		FName LoadLevelName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		bool bIsActivated = false;

};
