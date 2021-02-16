// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    if(PlayerPawn->GetIsPlayerAlive())
    {
        Destroy();
    }
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }
    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition() 
{
    if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }

    if (ReturnDistanceToPlayer() <= FireRange)
    {
        //Fire
        Fire();
    }
    
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn)
    {
        return 0.f;
    }
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()); 
}
