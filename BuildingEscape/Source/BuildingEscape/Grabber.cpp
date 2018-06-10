// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FindPhysicsHandle();
	FindInputComponent();
}

void UGrabber::FindInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("inputComponent was found on %s"), *GetOwner()->GetName());
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("inputComponent is missing on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicsHandle()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle) {
		UE_LOG(LogTemp, Warning, TEXT("physicsHandle was found on %s"), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("physicsHandle is missing on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...



	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);
	FVector lineTraceEnd = location + rotation.Vector()*reach;

	if (physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(lineTraceEnd);
	}

	

}

void UGrabber::Grab()
{
	FHitResult hitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
	AActor* actorHit = hitResult.GetActor();

	if (actorHit) {
		physicsHandle->GrabComponent(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	physicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult result;

	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);


	FVector lineTraceEnd = location + rotation.Vector()*reach;


	FCollisionQueryParams params(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT result,
		location,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		params);
	AActor* hitActor = result.GetActor();
	if (hitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *hitActor->GetName());
	}

	return result;
}

