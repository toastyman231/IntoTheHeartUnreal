// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LegacyCameraShake.h"
#include "GameFramework/Character.h"
#include "OverworldCharacter.generated.h"

UCLASS()
class INTOTHEHEARTUNREAL_API AOverworldCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOverworldCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShakeBase> ShakeProfile;

private:
	void MoveFB(float Value);
	void MoveLR(float Value);
	void RotateYaw(float Value);
	void RotatePitch(float Value);

private:
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
		float RotationSpeed = 1.0f;
};
