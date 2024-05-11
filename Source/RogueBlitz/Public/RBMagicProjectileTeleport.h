// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RBMagicProjectile.h"
#include "RBMagicProjectileTeleport.generated.h"

/**
 * 
 */
UCLASS()
class ROGUEBLITZ_API ARBMagicProjectileTeleport : public ARBMagicProjectile
{
	GENERATED_BODY()
	
public:
	// Default constructor (no arguments)
	ARBMagicProjectileTeleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void TeleportOnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void TeleportOnElapsedTime();
	void TeleportPlayer(const FVector& DestLocation);
	FTimerHandle TimerHandle_Teleport;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ExplosionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TeleportElapsedTime = 1.0f;
};
