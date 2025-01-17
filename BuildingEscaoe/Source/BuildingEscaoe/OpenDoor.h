// copyright Andrzej Kantor 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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
		FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//returns total mass on plate in kg
	float GetTotalMassOnPlate(ATriggerVolume*);

	virtual void Open() ;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate1 = nullptr;
private:
	UPROPERTY(EditAnywhere)
		float OpeningMass = 50.f;

	AActor *DoorOwner = nullptr;	   
};
