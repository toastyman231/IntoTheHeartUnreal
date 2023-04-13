// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlantState.generated.h"

UENUM()
enum PlantState
{
	Off     UMETA(DisplayName = "Off"),
	FadeIn      UMETA(DisplayName = "FadeIn"),
	On   UMETA(DisplayName = "On"),
	FadeOut      UMETA(DisplayName = "FadeOut"),
};

UENUM()
enum RotatingPlantState
{
	Left     UMETA(DisplayName = "Off"),
	GoingRight      UMETA(DisplayName = "FadeIn"),
	Right   UMETA(DisplayName = "On"),
	GoingLeft      UMETA(DisplayName = "FadeOut"),
};
