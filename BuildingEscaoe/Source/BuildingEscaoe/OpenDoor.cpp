// copyright Andrzej Kantor 2019

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine.h" 

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing Pressure plate."), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//hold the player on the ground
	//FVector ActorLocation = ActorThatOpens->GetActorLocation();
	//ActorLocation.Z = GroundLocation;
	//ActorThatOpens->SetActorLocation(ActorLocation);

	// poll trigger volume every frame 
	//if the actor that opens is on the volume then we open the door
	if (GetTotalMassOnPlate() > OpeningMass) 
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> PressurePlateOverlappingActors;

	//find all overlapping actors
	if (!PressurePlate) {return 1.f; 	}
	PressurePlate->GetOverlappingActors(OUT PressurePlateOverlappingActors);

	//iterate through them adding their masses
	for (const auto* ActorsOnPlate : PressurePlateOverlappingActors)
	{
		TotalMass += ActorsOnPlate->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Mass on plate equals: %f"), TotalMass);
	}

	return TotalMass;
}
