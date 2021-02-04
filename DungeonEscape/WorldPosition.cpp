// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// UE_LOG(LogTemp, Warning, TEXT("This is a warning!"));
	// UE_LOG(LogTemp, Error, TEXT("Error!"));
	// UE_LOG(LogTemp, Display, TEXT("This is not a warning!"));

	FString ObjectName = GetOwner() -> GetName();
	UE_LOG(LogTemp, Warning, TEXT("This is component is attached to %s"), *ObjectName);

	//Use GetActorTransform to return scale and rotation along with position
	//or use GetActorTransform().GetLocation()
	FString ObjectPosition = GetOwner() -> GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("This is component is at location %s"), *ObjectPosition);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

