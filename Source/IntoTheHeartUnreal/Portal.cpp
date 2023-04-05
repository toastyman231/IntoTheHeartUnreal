// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

#include "OverworldCharacter.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(DefaultRoot);

	PortalCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollider"));
	PortalCollider->SetupAttachment(DefaultRoot);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	PortalCollider->OnComponentBeginOverlap.AddDynamic(this, &APortal::OverlapBegin);
	SequenceActor->SequencePlayer->OnFinished.AddDynamic(this, &APortal::LoadLevelOnSequenceFinished);
}

void APortal::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AOverworldCharacter* Player = Cast<AOverworldCharacter>(OtherActor))
	{
		SequenceActor->SequencePlayer->Play();
	}
}

void APortal::LoadLevelOnSequenceFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
