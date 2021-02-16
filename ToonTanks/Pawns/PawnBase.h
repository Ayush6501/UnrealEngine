// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();
	virtual void HandleDestruction();
	void PawnDestroyed();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))	
	UCapsuleComponent *CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem *DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase *DeathSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> DeathShake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	UHealthComponent *HealthComponent;

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();
};
