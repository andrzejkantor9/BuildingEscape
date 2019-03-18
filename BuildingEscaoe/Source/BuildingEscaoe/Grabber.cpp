// copyright Andrzej Kantor 2019

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandleComponent();
	SetupInputComponent();
}

//look for attached physics handle
void UGrabber::PhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Object: %s is missing the Physics Handle Component."), *GetOwner()->GetName())
	}
}

//look for attached input component (only appears during runtime)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		///bind the input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Object: %s is missing the Input Component."), *GetOwner()->GetName())
	}
}

void UGrabber::MoveHoldObject()
{
	//if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		//move the object that we are holding
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveHoldObject();

}

void UGrabber::Grab()
{
	//try and reach any actor with physics collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); //gets the mesh in our case
	AActor* ActorHit = HitResult.GetActor();
	
	//if we hit something then attach physics
	if (ActorHit) {
	///attach physics handle 
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None, //no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true //allow rotation
		);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector LineTraceEnd = GetLineTraceEnd();
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	///ray-cast out to reacch distancez
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		(FName(TEXT("")), false, GetOwner())
	);

	return HitResult;
}

FVector UGrabber::GetLineTraceEnd()
{
	//tripple slashes make comments unrelated to line below
	/// Get the player veiwport this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * DebugLineReach;
}