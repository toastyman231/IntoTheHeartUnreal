// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSave.generated.h"

/**
 * 
 */
UCLASS()
class INTOTHEHEARTUNREAL_API USettingsSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MasterVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SFXVolume;

};
