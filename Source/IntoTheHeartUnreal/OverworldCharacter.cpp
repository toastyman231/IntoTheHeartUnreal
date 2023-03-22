// Fill out your copyright notice in the Description page of Project Settings.


#include "OverworldCharacter.h"

// Sets default values
AOverworldCharacter::AOverworldCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOverworldCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverworldCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetVelocity().SquaredLength() != 0)
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(ShakeProfile);
	else
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StopAllCameraShakes(false);
}

// Called to bind functionality to input
void AOverworldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AOverworldCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AOverworldCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("RotateYaw"), this, &AOverworldCharacter::RotateYaw);
	PlayerInputComponent->BindAxis(TEXT("RotatePitch"), this, &AOverworldCharacter::RotatePitch);
}

void AOverworldCharacter::MoveFB(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
}

void AOverworldCharacter::MoveLR(float Value)
{
	AddMovementInput(-GetActorRightVector(), Value * MoveSpeed);
}

void AOverworldCharacter::RotateYaw(float Value)
{
	AddControllerYawInput(Value * RotationSpeed);
}

void AOverworldCharacter::RotatePitch(float Value)
{
	AddControllerPitchInput(Value * RotationSpeed);
}

