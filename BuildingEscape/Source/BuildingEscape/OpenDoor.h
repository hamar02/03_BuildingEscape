// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CloseDoor();

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;
	
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.f;
	float lastDoorOpenTime;

	AActor* owner = nullptr;
	AActor* player = nullptr;
	FRotator openRotation;
	FRotator closeRotation;

	UPROPERTY(EditAnywhere)
	float doorAngle = 90.f;

	UPROPERTY(EditAnywhere)
	bool reverseOpenAngle = false;
};
