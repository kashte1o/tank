// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{

	FireProjecttile = 0,
	FireTrace = 1,
};
UCLASS()
class TANK_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
