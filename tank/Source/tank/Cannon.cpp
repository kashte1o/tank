// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
ACannon::ACannon()
{

	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	RootComponent = sceneComp;
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComp);
	ProjecttileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjecttileSpawnPoint"));
	ProjecttileSpawnPoint->SetupAttachment(CannonMesh);

}




	

	/*void ACannon::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

	}
	*/
	void ACannon::Fire()
	{
		if (!IsReadyToFire())
		{
			return;
		}
		bReadyToFire = false;
		if (CannonType == ECannonType::FireProjecttile)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projecttile %f")));
		}
		else
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace %f")));
		}

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
	}



	void ACannon::Reload()
	{

		bReadyToFire = true;
	}

	bool ACannon::IsReadyToFire()
	{
		return bReadyToFire;

	}

	void ACannon::BeginPlay()
	{
		Super::BeginPlay();
		Reload();
	}
