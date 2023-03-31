// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PuzzlePawn.generated.h"

UCLASS()
class INTOTHEHEARTUNREAL_API APuzzlePawn : public APawn
{
    GENERATED_BODY()

public:
    APuzzlePawn();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool CanRotate;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* SpringArm;

    void OnMouseDragX(float AxisValue);
    void OnMouseDragY(float AxisValue);

    FVector2D LastMousePosition;
};