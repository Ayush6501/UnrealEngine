// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DoorOpen.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	float CurrentYaw, InitialYaw;
	UPROPERTY(EditAnyWhere)
	float OpenAngle = 90.f;
	
	UPROPERTY(EditAnyWhere)
	ATriggerVolume* PressurePlate = nullptr;

	float DoorLastOpened = 0.f;
	UPROPERTY(EditAnyWhere)
	float DoorCloseDelay = .55f;

	UPROPERTY(EditAnyWhere)
	float OpenDoorSpeed = 0.9f;
	UPROPERTY(EditAnyWhere)
	float ClosedDoorSpeed = 2.f;
	
	float TotalMassofActor() const; 

	UPROPERTY(EditAnyWhere)
	float MinMassToOpenDoor = 50.f;
};
