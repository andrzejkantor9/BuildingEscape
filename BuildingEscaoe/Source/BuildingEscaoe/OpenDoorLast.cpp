// copyright Andrzej Kantor 2019

#include "OpenDoorLast.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UOpenDoorLast::UOpenDoorLast()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorLast::BeginPlay()
{
	Super::BeginPlay();

}

void UOpenDoorLast::Open() 
{
	if(LetMainDoorOpen())
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}


// Called every frame
void UOpenDoorLast::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UOpenDoorLast::LetMainDoorOpen()
{
	if (!PressurePlate2 || !PressurePlate3 || !PressurePlate4) {return false; }
	

	int NumberOfTriggerPressurePlates = 0;

	if (GetTotalMassOnPlate(PressurePlate1) > OpeningMass1) { ++NumberOfTriggerPressurePlates; 	}
	if (GetTotalMassOnPlate(PressurePlate2) > OpeningMass1) { ++NumberOfTriggerPressurePlates; }
	if (GetTotalMassOnPlate(PressurePlate3) > OpeningMass1) { ++NumberOfTriggerPressurePlates; }
	if (GetTotalMassOnPlate(PressurePlate4) > OpeningMass1) { ++NumberOfTriggerPressurePlates; }
	//if all 4 triggers are pushed then true - open the main door
		//iterate through all 4 triggers
	//else - false, do not open the main door
	if (NumberOfTriggerPressurePlates == 4) { return true; }
	
	return false;
}