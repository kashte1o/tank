// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

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
		if (ProjectileAmount == 0)
		{
			return;
		}
		if (CannonType == ECannonType::FireProjecttile)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projecttile %f")));
		}
		else
			if (CannonType == ECannonType::FireTrace)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace %f")));
		}

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
		
		ProjectileAmount = ProjectileAmount - 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Projectile Amount = %f"), ProjectileAmount));
	}

	void ACannon::FireSpecial()
	{
		if (!IsReadyToFire())
		{
			return;
		}
		bReadyToFire = false;
		
		if (ProjectileAmount == 0)
		{
			return;
		}
		
		if (CannonType == ECannonType::FireProjecttile)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire projecttile special %f")));
		}
		else
			if(CannonType == ECannonType::FireTraceSpecial)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace special %f")));
		}

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);

		ProjectileAmount = ProjectileAmount - 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Projectile Amount = %f"),  ProjectileAmount));
	}

	void ACannon::AutoFire()
	{
		if (!IsReadyToFire())
		{
			return;
		}
		bReadyToFire = false;

		if (ProjectileAmount == 0)
		{
			return;
		}

		if (CannonType == ECannonType::FireProjecttile)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Auto Fire projectile %f")));
		}
		else
			if (CannonType == ECannonType::FireTrace)
			{

				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Auto Fire trace %f")));
			}

		/*GetWorld()->GetTimerManager().SetTimer(AutoTimer, this, &ACannon::ReloadAuto, 1 / FireRate, false);

		ProjectileAmount = ProjectileAmount - 1;
		ProjectileAmount = ProjectileAmount - 1;
		ProjectileAmount = ProjectileAmount - 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Projectile Amount = %f"), ProjectileAmount));
		if (ProjectileAmount == 0)
		{
			GetWorldTimerManager().ClearTimer(AutoTimer);
		}
			for (ProjectileAmount = 10; ProjectileAmount = 0; ProjectileAmount - 3)
			{
				GetWorld()->GetTimerManager().SetTimer(AutoTimer, this, &ACannon::ReloadAuto, 1 / FireRate, false);
				GetWorldTimerManager().ClearTimer(AutoTimer);

			}
			*/
		if ((ProjectileAmount > 0))
		{
			GetWorld()->GetTimerManager().SetTimer(AutoTimer, this, &ACannon::ReloadAuto, 10 / FireRate, false);
			ProjectileAmount = ProjectileAmount - 1;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Projectile Amount = %f"), ProjectileAmount));
			ProjectileAmount = ProjectileAmount - 1;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Projectile Amount = %f"), ProjectileAmount));
			ProjectileAmount = ProjectileAmount - 1;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Projectile Amount = %f"), ProjectileAmount));
			
		}
		else
		{
			GetWorldTimerManager().ClearTimer(AutoTimer);
		}
		
	}
	

	
	void ACannon::Reload()
	{

		bReadyToFire = true;
		
	}
	void ACannon::ReloadAuto()
	{

		bReadyToFire = true;
		GetWorld()->GetTimerManager().SetTimer(AutoTimer, this, &ACannon::Fire, 1 / FireRate, true, 10 / FireRate);
	}

	bool ACannon::IsReadyToFire()
	{
		return bReadyToFire;

	}

	
	void ACannon::BeginPlay()
	{
		Super::BeginPlay();
		Reload();
		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Projectile Amount = %f"), ProjectileAmount));
	}
	