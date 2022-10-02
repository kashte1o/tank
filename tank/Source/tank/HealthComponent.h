// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "HealthComponent.generated.h"

DECLARE_EVENT(UHealthComponent, FOnDie);
DECLARE_EVENT_OneParam(UHealthComponent, FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_API UHealthComponent : public UActorComponent
{
	
	GENERATED_BODY()
		
	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health value")
			float MaxHealth = 10;
		
	
		
	public:
		
		FOnDie OnDie;
		FOnHealthChanged OnHealthChanged;
		void AddHealth(float newHealth);
		void TakeDamage(FDamageData DamageData);
		float GetHealth() const;

		UFUNCTION(BlueprintCallable)
		float GetHealthState() const;
	protected:
		
		UHealthComponent();
		virtual void BeginPlay() override;
		
		float CurrentHealth;
	

		
		
};
