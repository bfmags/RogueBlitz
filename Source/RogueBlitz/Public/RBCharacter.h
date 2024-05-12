// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RBCharacter.generated.h"

// uses forward declaration (partial inclusion for incomplete type) to avoid circular
class USpringArmComponent;
class UCameraComponent;
class URBInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ROGUEBLITZ_API ARBCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARBCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> PrimaryAttackProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> SecondaryAttackProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Teleport")
	TSubclassOf<AActor> PrimaryTeleportProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	URBInteractionComponent* InteractionComponent;
	
	void PrimaryAttack();
	void SecondaryAttack();
	void PrimaryTeleport_TimeElapsed();
	void FireProjectile(TSubclassOf<AActor> Projectile);
	void PrimaryInteract();
	void MoveForward(float Value);
	void MoveRight(float Value);

	FTimerHandle TimerHandle_PrimaryAttack;
	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack_TimeElapsed();
	void PrimaryTeleport();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Debug
	void DrawDebugScreenAids() const;

	// Trace range in UU
	const float MaxTraceDistance = 3000;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
