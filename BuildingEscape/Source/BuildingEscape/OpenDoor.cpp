// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


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

	// ...
	if (!pressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("pressurePlate was found on %s"), *GetOwner()->GetName());
	}
	owner = GetOwner();
	closeRotation = owner->GetActorRotation();
	openRotation = closeRotation;
}





float UOpenDoor::GetTotalMassOfActorsOnPlate() const
{
	float weight = 0;
	if (pressurePlate) {
		TArray<AActor*> overlappingActors;
		pressurePlate->GetOverlappingActors(OUT overlappingActors);
		for (const auto& actor : overlappingActors) {
			weight += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}

	}


	return weight;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GetTotalMassOfActorsOnPlate()>=requiredWeight) {
		OnOpen.Broadcast();		
	}else{
		OnClose.Broadcast();
	}

}


