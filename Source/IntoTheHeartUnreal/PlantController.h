// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OverworldCharacter.h"
#include "PlantState.h"
#include "PlantController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTOTHEHEARTUNREAL_API UPlantController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlantController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AlwaysOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeFadeIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeFadeOut;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void ManageState();

	UFUNCTION()
		virtual void CheckState();

	float Timer = 0.f;

	const float MAX_ANGLE = 30.f;

	const float OFF_INTENSITY = 2.5f;

	const float ON_INTENSITY = 4.f;

	UPROPERTY()
		UStaticMeshComponent* ConeMesh;

	UPROPERTY()
		UMaterial* ConeMaterial;

	UPROPERTY()
		TEnumAsByte<PlantState> State;

	UPROPERTY()
		FVector OriginalConeScale;

	UPROPERTY()
		FVector EmptyCone;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
