// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	private:
		int32 GetTargetTurretCount();
		void HandleGameStart();
		void HandleGameOver(bool PlayerWon);

		APlayerControllerBase *PlayerControllerRef;
		APawnTank *PlayerTank;
		int32 TargetTurret = 0;

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameLoop")
		int32 StartDelay;

		virtual void BeginPlay() override;
		UFUNCTION(BlueprintImplementableEvent)		
		void GameStart();
		UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool PlayerWon);

	public:
		void ActorDied(AActor * DeadActor);
};
