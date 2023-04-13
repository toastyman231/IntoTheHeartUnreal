// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlantController.h"

#include "Components/AudioComponent.h"

void URotatingPlantController::BeginPlay()
{
	Head = Cast<USceneComponent>(GetOwner()->GetComponentsByTag(UAudioComponent::StaticClass(), FName("Head"))[0]);
	LEFT_ANGLE = FRotator(Head->GetRelativeRotation().Euler().Y, MinAngle, Head->GetRelativeRotation().Euler().X);
	RIGHT_ANGLE = FRotator(Head->GetRelativeRotation().Euler().Y, MaxAngle, Head->GetRelativeRotation().Euler().X);

	Super::BeginPlay();
}

void URotatingPlantController::ManageState()
{
	switch(RotateState)
	{
	case RotatingPlantState::Left:
		Head->SetRelativeRotation(LEFT_ANGLE);
		break;
	case RotatingPlantState::GoingRight:
		Head->SetRelativeRotation(FMath::Lerp(LEFT_ANGLE, RIGHT_ANGLE, RotateTimer / TimeRotate));
		break;
	case RotatingPlantState::Right:
		Head->SetRelativeRotation(RIGHT_ANGLE);
		break;
	case RotatingPlantState::GoingLeft:
		Head->SetRelativeRotation(FMath::Lerp(RIGHT_ANGLE, LEFT_ANGLE, RotateTimer / TimeRotate));
		break;
	default: break;
	}

	CheckState();

	if (!AlwaysOn) Super::ManageState();
}

void URotatingPlantController::CheckState()
{
	float timeToBeat = 0.f;

	switch (RotateState)
	{
	case RotatingPlantState::Left:
		timeToBeat = TimeStop;
		break;
	case RotatingPlantState::GoingRight:
		timeToBeat = TimeRotate;
		break;
	case RotatingPlantState::Right:
		timeToBeat = TimeStop;
		break;
	case RotatingPlantState::GoingLeft:
		timeToBeat = TimeRotate;
		break;
	default: break;
	}

	if (RotateTimer >= timeToBeat)
	{
		RotateTimer = 0.f;
		float val = (static_cast<int>(RotateState) + 1) % 4;
		RotateState = static_cast<RotatingPlantState>(val);
	}

	if (!AlwaysOn) Super::CheckState();
}

void URotatingPlantController::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	RotateTimer += DeltaTime;
	ManageState();

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
