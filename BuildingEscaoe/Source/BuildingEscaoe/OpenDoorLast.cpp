// copyright Andrzej Kantor 2019

#include "OpenDoorLast.h"

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

	UE_LOG(LogTemp, Warning, TEXT("UOPENDOORLASTHASLOADED!"));

}


// Called every frame
void UOpenDoorLast::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
