
#include <Kismet/GameplayStatics.h>
#include <Components/PointLightComponent.h>
#include "Components\StaticMeshComponent.h"
#include "Components\BoxComponent.h"
#include "MapLoader.h"
#include "TankPawn.h"


AMapLoader::AMapLoader()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* SceneComp =CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;
	
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneComp);
	
	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ActivatedLight"));
	ActivatedLight->SetupAttachment(SceneComp);

	DeactivatedLight =CreateDefaultSubobject<UPointLightComponent>(TEXT("DeactivatedLight"));
	DeactivatedLight->SetupAttachment(SceneComp);
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMapLoader::OnTriggerOverlapBegin);
	
	


}



void AMapLoader::BeginPlay()
{
	Super::BeginPlay();
	SetActivatedLights();

}
void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	bIsActivated = NewIsActivated;
	SetActivatedLights();

}

void AMapLoader::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActivated)
	{
		return;
	}
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (TankPawn)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}

}
void AMapLoader::SetActivatedLights()
{
	ActivatedLight->SetHiddenInGame(!bIsActivated);
	DeactivatedLight->SetHiddenInGame(bIsActivated);

}