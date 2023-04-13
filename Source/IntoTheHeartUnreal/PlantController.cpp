// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantController.h"

// Sets default values for this component's properties
UPlantController::UPlantController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlantController::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> Children;

	Cast<UChildActorComponent>(
		GetOwner()->GetComponentByClass(UChildActorComponent::StaticClass()))->GetChildrenComponents(true, Children);
	ConeMesh = Cast<UStaticMeshComponent>(Children[1]);

	OriginalConeScale = ConeMesh->GetRelativeScale3D();
	EmptyCone = FVector(0.f, 0.f, OriginalConeScale.Z);

	ConeMesh->OnComponentBeginOverlap.AddDynamic(this, &UPlantController::OverlapBegin);

	ConeMaterial = ConeMesh->GetMaterial(0)->GetMaterial();

	if (AlwaysOn)
	{
		UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(ConeMaterial, ConeMesh);
		dynamicMaterial->SetVectorParameterValue(FName("Emission"), FLinearColor::Red * ON_INTENSITY);
		ConeMesh->SetMaterial(0, dynamicMaterial);

		ConeMesh->SetGenerateOverlapEvents(true);
	} else
	{
		UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(ConeMaterial, ConeMesh);
		dynamicMaterial->SetVectorParameterValue(FName("Emission"), FLinearColor::Yellow * OFF_INTENSITY);
		ConeMesh->SetMaterial(0, dynamicMaterial);

		ConeMesh->SetGenerateOverlapEvents(false);
	}
}

void UPlantController::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AOverworldCharacter* Player = Cast<AOverworldCharacter>(OtherActor))
	{
		Player->LoseGame();
	}
}

void UPlantController::ManageState()
{
	UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(ConeMaterial, ConeMesh);

	switch(State)
	{
	case PlantState::Off: 
		ConeMesh->SetRelativeScale3D(EmptyCone);
		break;
	case PlantState::FadeIn: 
		ConeMesh->SetRelativeScale3D(FMath::Lerp(EmptyCone, OriginalConeScale, Timer / TimeFadeIn));
		break;
	case PlantState::On:
		dynamicMaterial->SetVectorParameterValue(FName("Emission"), FLinearColor::Red * ON_INTENSITY);
		ConeMesh->SetMaterial(0, dynamicMaterial);
		ConeMesh->SetRelativeScale3D(OriginalConeScale);
		ConeMesh->SetGenerateOverlapEvents(true);
		break;
	case PlantState::FadeOut:
		dynamicMaterial->SetVectorParameterValue(FName("Emission"), FLinearColor::Yellow * OFF_INTENSITY);
		ConeMesh->SetMaterial(0, dynamicMaterial);
		ConeMesh->SetRelativeScale3D(FMath::Lerp(OriginalConeScale, EmptyCone, Timer / TimeFadeOut));
		ConeMesh->SetGenerateOverlapEvents(false);
		break;
	default: break;
	}

	CheckState();
}

void UPlantController::CheckState()
{
	float timeToBeat = 0.f;

	switch(State)
	{
	case PlantState::Off:
		timeToBeat = TimeOff;
		break;
	case PlantState::FadeIn:
		timeToBeat = TimeFadeIn;
		break;
	case PlantState::On:
		timeToBeat = TimeOn;
		break;
	case PlantState::FadeOut:
		timeToBeat = TimeFadeOut;
		break;
	default: break;
	}

	if (Timer >= timeToBeat)
	{
		Timer = 0.f;
		float val = (static_cast<int>(State) + 1) % 4;
		State = static_cast<PlantState>(val);
	}
}


// Called every frame
void UPlantController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if (!AlwaysOn) ManageState();
}

