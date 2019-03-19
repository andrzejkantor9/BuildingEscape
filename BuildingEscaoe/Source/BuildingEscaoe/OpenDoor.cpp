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

}

void UOpenDoor::OpenDoor()
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = OpenAngle;
	GetOwner()->SetActorRotation(DoorRotation);
	DoorClosed = false;
}

void UOpenDoor::CloseDoor()
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw -= OpenAngle;
	GetOwner()->SetActorRotation(DoorRotation);
	DoorClosed = true;
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
	if (GetTotalMassOnPlate() > 50.f) //TODO change to constexpr variable
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay && !DoorClosed)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> PressurePlateOverlappingActors;

	//find all overlapping actors
	PressurePlate->GetOverlappingActors(OUT PressurePlateOverlappingActors);

	//iterate through them adding their masses
	for (const auto* ActorsOnPlate : PressurePlateOverlappingActors)
	{
		TotalMass += ActorsOnPlate->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Mass on plate equals: %f"), TotalMass);
	}

	return TotalMass;
}
