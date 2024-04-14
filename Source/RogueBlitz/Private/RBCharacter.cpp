// Fill out your copyright notice in the Description page of Project Settings.
#include "RBCharacter.h"

#include <ThirdParty/hlslcc/hlslcc/src/hlslcc_lib/ir.h>

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "RBInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARBCharacter::ARBCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<URBInteractionComponent>("InteractionComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ARBCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// -- Rotation Visualization -- //
	constexpr float DrawScale = 100.0f;
	constexpr float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	const FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	const FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void ARBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARBCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARBCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ARBCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ARBCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed,this, &ARBCharacter::PrimaryInteract);
}

void ARBCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARBCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ARBCharacter::PrimaryAttack_TimeElapsed()
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	const FTransform SpawnTransformMatrix = FTransform( GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransformMatrix, SpawnParams);
}

void ARBCharacter::PrimaryInteract()
{
	if(InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
}

void ARBCharacter::MoveForward(float Value)
{
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;
	
	AddMovementInput(ControlRotator.Vector(), Value);
}

void ARBCharacter::MoveRight(float Value)
{
	// X - Forward red
	// Y - Right green
	// Z - Up blue
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRotator).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}