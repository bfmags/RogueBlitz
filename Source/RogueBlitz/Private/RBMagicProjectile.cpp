// Fill out your copyright notice in the Description page of Project Settings.

#include "RBMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARBMagicProjectile::ARBMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARBMagicProjectile::OnActorOverlap);

	/*SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);*/
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

	// Setup Audio effects components
	SoundComponent = CreateDefaultSubobject<UAudioComponent>("FlightSoundComponent");
	SoundComponent->SetupAttachment(RootComponent);
	SoundComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
	SoundComponent->bAutoActivate = false;
}

void ARBMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (IsValid(OtherActor) && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>
													(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (IsValid(AttributeComponent))
		{
			SoundComponent->Stop();
			if (ImpactAudioCue->IsValidLowLevelFast()) {
				UGameplayStatics::PlaySoundAtLocation(this, ImpactAudioCue, OtherActor->GetActorLocation());
			}

			AttributeComponent->ApplyHealthChange(-20.0f);
			Destroy();
		}

	}
}

// Called when the game starts or when spawned
void ARBMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (FlightAudioCue->IsValidLowLevelFast()) {
		SoundComponent->SetSound(FlightAudioCue);

		float startTime = 9.f;
		float volume = 1.0f;
		float fadeTime = 1.0f;
		SoundComponent->FadeIn(fadeTime, volume, startTime);
	}

}

// Called every frame
void ARBMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


