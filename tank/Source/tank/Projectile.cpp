#include "Projectile.h"
#include <Components\SceneComponent.h>
#include "Components/SphereComponent.h"
#include "DamageTaker.h"
#include "GameStructs.h"
#include "Particles\ParticleSystem.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles\ParticleSystemComponent.h"
//#include "Cannon.cpp"
//#include "Particles/ParticleSystemComponent.h"


AProjectile::AProjectile()
{
 
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision -> SetupAttachment(SceneComp);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(SphereCollision);

	
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate,true, MoveRate);

}



void AProjectile::Move()
{

	FVector movePosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(movePosition);

}

void AProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(OtherActor);

		if (DamageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = GetOwner();
			damageData.DamageMaker = this;

			DamageTakerActor->TakeDamage(damageData);
			
		}
		else
		{
			OtherActor->Destroy();
		}
		
	}
	Template = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());

	UE_LOG(LogTemp, Warning, TEXT("Projectile overlap : %s"), *OtherActor->GetName());
	//HitEnemy->ActivateSystem();
	//Template = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
	Destroy();
	

}



