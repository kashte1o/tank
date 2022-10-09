

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"


UCLASS()
class TANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectile();
	void Start();
	FTimerHandle MoveTimer;

protected:
	
	//virtual void BeginPlay() override;
	void Move();

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool	bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		float MoveRate = 0.005f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		class UParticleSystemComponent* HitEnemy;
	
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		UParticleSystemComponent* Template;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
			class UParticleSystem* Particle;

		

		

		
};
