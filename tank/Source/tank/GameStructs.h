// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{

	FireProjecttile = 0 UMETA(DisplayName = "Use Projecttile"),
	FireTrace = 1 UMETA(DisplayName = "Use trace"),
	FireProjecttileSpecial = 2 UMETA(DisplayName = "Use Projecttile Special"),
	FireTraceSpecial = 3 UMETA(DisplayName = "Use Trace Special"),
	AutoFireTrace = 4 UMETA(DisplayName = "Use Trace Auto"),
	AutoFireProjectile = 5 UMETA(DisplayName = "Use Projectile Auto"),
};


USTRUCT()
struct FDamageData
{
	GENERATED_BODY()
		
		UPROPERTY()
		float DamageValue;
	
	UPROPERTY()
		AActor* Instigator;

	
	
	UPROPERTY()
		AActor* DamageTaker;
	
	UPROPERTY()
		AActor* DamageMaker;

};
UCLASS()
class TANK_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
