// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RBGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RBItemChest.generated.h"

UCLASS()
class ROGUEBLITZ_API ARBItemChest : public AActor, public IRBGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARBItemChest();

	void Interact_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(VisibleAnywhere);
	float TargetPitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
