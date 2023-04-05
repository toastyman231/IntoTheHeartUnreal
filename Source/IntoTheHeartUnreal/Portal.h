// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "LevelSequenceActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequencePlayer.h"
#include "Portal.generated.h"

UCLASS()
class INTOTHEHEARTUNREAL_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(EditAnywhere)
		ALevelSequenceActor* SequenceActor;

	UPROPERTY(EditAnywhere)
		FName LevelToLoad;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void LoadLevelOnSequenceFinished();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
		USceneComponent* DefaultRoot = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* PortalCollider;
};
