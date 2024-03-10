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

UCLASS()
class ROGUEBLITZ_API ARBCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARBCharacter();

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	URBInteractionComponent* InteractionComponent;
	
	void PrimaryAttack();
	void PrimaryInteract();
	void MoveForward(float Value);
	void MoveRight(float Value);

	FTimerHandle TimerHandle_PrimaryAttack;
	void PrimaryAttack_TimeElapsed();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
