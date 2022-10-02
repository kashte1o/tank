// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Projectile.h"

ACannon::ACannon()
{

	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	RootComponent = sceneComp;
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComp);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjecttileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);

}



	void ACannon::Fire()
	{
		if (!IsReadyToFire() || Shells <= 0)
		{
			return;
		}
		bReadyToFire = false;
		Shells--;

	
		if (CannonType == ECannonType::FireProjecttile)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projecttile")));
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), spawnParams);
			
			if (projectile)
			{
				projectile->Start();

			}
		}
		else
			if (CannonType == ECannonType::FireTrace)
			{

				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace %f")));
				FHitResult hitResult;
				FCollisionQueryParams traceParams;

				traceParams.bTraceComplex = true;
				traceParams.bReturnPhysicalMaterial = false;

				FVector Start = ProjectileSpawnPoint->GetComponentLocation();
				FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;


				if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, traceParams))
				{
					DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Purple, false, 1.0f, 0, 5.0f);
					if (hitResult.GetActor())
					{
						UE_LOG(LogTemp, Warning, TEXT("trace overlap : %s"), *hitResult.GetActor()->GetName());
						hitResult.GetActor()->Destroy();
					}
				}
				else
				{
					DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 2.0f);
				}
			}
		

		

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
		
		
		
	}

	void ACannon::FireSpecial()
	{
		if (!IsReadyToFire() || Shells <= 0)
		{
			return;
		}
		bReadyToFire = false;
		
		
		if (CannonType == ECannonType::FireProjecttile)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire projecttile special")));
		}
		else
			if(CannonType == ECannonType::FireTraceSpecial)
		{

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace special")));
		}

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);

		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Shells = %d"), Shells));
	}

	void ACannon::AutoFire()
	{
		if (!IsReadyToFire() || Shells <=0)
		{
			return;
		}
		bReadyToFire = false;
		GetWorld()->GetTimerManager().SetTimer(AutoTimer, this, &ACannon::ReloadAuto, BustInterval, true, 0.0f);

		
	}
	

	
	void ACannon::Reload()
	{

		bReadyToFire = true;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Shells: %d"), Shells));
		
	}
	
	
	void ACannon::ReloadAuto()
	{

		if (CurrentBurts == BustSize)
		{
			GetWorld()->GetTimerManager().ClearTimer(AutoTimer);
			bReadyToFire = true;
			CurrentBurts = 0;
			Shells--;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Shells: %d"), Shells));
			return;
		}
		CurrentBurts++;
		if (CannonType == ECannonType::FireProjecttile)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), spawnParams);

			if (projectile)
			{
				projectile->Start();

			}
		}
		else
		{
			FHitResult hitResult;
			FCollisionQueryParams traceParams;

			traceParams.bTraceComplex = true;
			traceParams.bReturnPhysicalMaterial = false;

			FVector Start = ProjectileSpawnPoint->GetComponentLocation();
			FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;
			if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, traceParams))
			{
				DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Purple, false, 1.0f, 0, 5.0f);
				if (hitResult.GetActor())
				{
					UE_LOG(LogTemp, Warning, TEXT("trace overlap : %s"), *hitResult.GetActor()->GetName());
					hitResult.GetActor()->Destroy();
				}
			}
			else
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 2.0f);
			}
		}
	}

	bool ACannon::IsReadyToFire()
	{
		return bReadyToFire;

	}

	void ACannon::AddShells(int32 newShells)
	{
		Shells += newShells;



	}


	

	
	void ACannon::BeginPlay()
	{
		Super::BeginPlay();
		Reload();
		
		
	}
	
	
