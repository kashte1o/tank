#include "AmmoBox.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"



#include "AmmoBox.h"
#include "TankPawn.h"
#include "Cannon.h"
#include "Cannon.cpp"


AAmmoBox::AAmmoBox()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
		RootComponent = SceneComp;
		AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
		AmmoMesh->SetupAttachment(SceneComp);
		AmmoMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
		AmmoMesh->SetCollisionProfileName("OverlapAll");
		AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AmmoMesh->SetGenerateOverlapEvents(true);
}




void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{
		TankPawn->SetupCannon(CannonClass);
		
		
	}
	Destroy();
}


