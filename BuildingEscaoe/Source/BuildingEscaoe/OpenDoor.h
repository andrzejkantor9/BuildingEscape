// copyright Andrzej Kantor 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAOE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest OnOpenRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

private:
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate = nullptr;

	AActor *DoorOwner = nullptr;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	float LastDoorOpenTime = 0.f;
	float GroundLocation = 0.f;
	bool DoorClosed = true;

	//returns total mass on plate in kg
	float GetTotalMassOnPlate();
};
