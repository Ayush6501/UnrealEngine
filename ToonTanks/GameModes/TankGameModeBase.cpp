// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"


void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor * DeadActor) 
{
    UE_LOG(LogTemp, Warning, TEXT("A Pawn just Died"));
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnableState(false);
        }
    }
    else if(APawnTurret *DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        if(--TargetTurret == 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart() 
{
    TargetTurret = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart();

    if(PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnableState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
            &APlayerControllerBase::SetPlayerEnableState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, 3.0f, false);
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount() 
{
    TArray<AActor*> TurretActor;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActor);
    return TurretActor.Num();
}
