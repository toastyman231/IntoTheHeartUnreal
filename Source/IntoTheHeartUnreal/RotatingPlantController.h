// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantController.h"
#include "RotatingPlantController.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class INTOTHEHEARTUNREAL_API URotatingPlantController : public UPlantController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void ManageState() override;
	virtual void CheckState() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeRotate;

protected:

	UPROPERTY()
		TEnumAsByte<RotatingPlantState> RotateState;

	float RotateTimer = 0.f;

	UPROPERTY()
		USceneComponent* Head;

	UPROPERTY()
		FRotator LEFT_ANGLE;

	UPROPERTY()
		FRotator RIGHT_ANGLE;
};
