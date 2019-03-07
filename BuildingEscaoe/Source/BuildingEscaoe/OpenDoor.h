// copyright Andrzej Kantor 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAOE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;

	AActor *DoorOwner;
	AActor *ActorThatOpens;	//remember - pawwn inherits from aactor

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	float LastDoorOpenTime = 0.f;
	float GroundLocation = 0.f;
	bool DoorClosed = true;
};
