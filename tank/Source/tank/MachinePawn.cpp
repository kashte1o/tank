


#include "MachinePawn.h"


AMachinePawn::AMachinePawn()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}


void AMachinePawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMachinePawn::SetupCannon()
{
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(newCannon, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}
