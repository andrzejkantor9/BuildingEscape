// copyright Andrzej Kantor 2019

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine.h"

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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	GroundLocation = ActorThatOpens->GetActorLocation().Z;
}

void UOpenDoor::OpenDoor()
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = OpenAngle;
	GetOwner()->SetActorRotation(DoorRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//hold the player on the ground
	FVector ActorLocation = ActorThatOpens->GetActorLocation();
	ActorLocation.Z = GroundLocation;
	ActorThatOpens->SetActorLocation(ActorLocation);

	// poll trigger volume every frame 
	//if the actor that opens is on the volume then we open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}
}

