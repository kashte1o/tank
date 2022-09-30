// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UHealthComponent::GetHealth() const
{
	return 0.0f;
}

float UHealthComponent::GetHealthState() const
{
	return 0.0f;
}



/*void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

*/

/*void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

*/