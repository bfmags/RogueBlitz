// Fill out your copyright notice in the Description page of Project Settings.


#include "RBMagicProjectileTeleport.h"

ARBMagicProjectileTeleport::ARBMagicProjectileTeleport()
{
	ExplosionComp = CreateDefaultSubobject<UParticleSystemComponent>("Explosion");
	ExplosionComp->SetupAttachment(SphereComp);
	
	// Initially hide the explosion component
	ExplosionComp->SetHiddenInGame(true);
	ExplosionComp->Deactivate();
}


void ARBMagicProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();

	// Bind the OnComponentHit event
	SphereComp->OnComponentHit.AddDynamic(this, &ARBMagicProjectileTeleport::TeleportOnHit);

	// Teleport after 2sec
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ARBMagicProjectileTeleport::TeleportOnElapsedTime, TeleportElapsedTime);

}

void ARBMagicProjectileTeleport::TeleportOnElapsedTime()
{
	TeleportPlayer(SphereComp->GetComponentLocation());
}

void ARBMagicProjectileTeleport::TeleportOnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check for valid collision
	if (IsValid(OtherActor) && OtherActor != GetInstigator())
	{
		TeleportPlayer(OtherActor->GetActorLocation());
	}
}

void ARBMagicProjectileTeleport::TeleportPlayer( const FVector& DestLocation)
{
	//clear timer
	GetWorldTimerManager().ClearTimer(TimerHandle_Teleport);
	
	ExplosionComp->ActivateSystem(true);
	ExplosionComp->SetHiddenInGame(false);
		
	EffectComp->Deactivate();

	if (IsValid(GetInstigator()))
	{
		GetInstigator()->TeleportTo(
			DestLocation,
			GetInstigator()->GetActorRotation(),
			false,
			false
			);
	}
}

void ARBMagicProjectileTeleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
