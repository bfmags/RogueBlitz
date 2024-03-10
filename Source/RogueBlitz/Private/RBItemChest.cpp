// Fill out your copyright notice in the Description page of Project Settings.

#include "RBItemChest.h"

// Sets default values
ARBItemChest::ARBItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 120;
	
}

void ARBItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(120,0,0));
}

// Called when the game starts or when spawned
void ARBItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARBItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

