// copyright Andrzej Kantor 2019

#pragma once

#include "CoreMinimal.h"
#include "OpenDoor.h"
#include "Components/ActorComponent.h"
#include "OpenDoorLast.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAOE_API UOpenDoorLast : public UOpenDoor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoorLast();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Open() ;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool LetMainDoorOpen();
private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate2 = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate3 = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate4 = nullptr;

	UPROPERTY(EditAnywhere)
		float OpeningMass1 = 50.f;
};
