// Fill out your copyright notice in the Description page of Project Settings.


#include "RBExplosiveBarrel.h"

// Sets default values
ARBExplosiveBarrel::ARBExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->bApplyImpulseOnDamage = true;
	MeshComponent->SetCollisionProfileName("PhysicsActor");
	
	RootComponent = MeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->Radius = 750.0f;
	RadialForceComponent->ImpulseStrength = 2500.0f;
	RadialForceComponent->bImpulseVelChange = true;

	// Leaving this on apply force on component tick
	RadialForceComponent->SetAutoActivate(false);

	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadialForceComponent->SetupAttachment(MeshComponent);

}

void ARBExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Callbacks
	MeshComponent->OnComponentHit.AddDynamic(this, &ARBExplosiveBarrel::OnHitCallback);
}


// Called when the game starts or when spawned
void ARBExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ARBExplosiveBarrel::OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
}

// Called every frame
void ARBExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

