
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "Projectile.h"
#include "Cannon.generated.h"
UCLASS()
class TANK_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACannon();
	void Fire();
	void FireSpecial();
	void AutoFire();
	void Reload();
	void ReloadAuto();
	bool IsReadyToFire();
	
	
	FTimerHandle ReloadTimer;
	FTimerHandle AutoTimer;
	void Change();
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<class AProjectile> ProjectileClass;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		ECannonType CannonType = ECannonType::FireProjecttile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	ECannonType CannonTypeSpecial = ECannonType::FireProjecttileSpecial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float ProjectileAmount = 12.0f;
	
	
	virtual void BeginPlay() override;
private:
	bool bReadyToFire = false;
};
