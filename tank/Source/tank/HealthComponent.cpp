


#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

}

void UHealthComponent::AddHealth(float newHealth)
{
	CurrentHealth += newHealth;
	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::TakeDamage(FDamageData DamageData)
{
	float takeDamageValue = DamageData.DamageValue;
	CurrentHealth -= takeDamageValue;
	if (CurrentHealth <= 0)
	{
		if (OnDie.IsBound())

			OnDie.Broadcast();
	}
		else
		{
			if (OnHealthChanged.IsBound())
			
				OnHealthChanged.Broadcast(takeDamageValue);
			
		}

	

}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthState() const
{
	return CurrentHealth/MaxHealth;
}







/*void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

*/