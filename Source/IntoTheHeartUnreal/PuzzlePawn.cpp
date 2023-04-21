// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

APuzzlePawn::APuzzlePawn()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	PrimaryActorTick.bCanEverTick = true;

	// Create the SpringArm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;
	//SpringArm->bUsePawnControlRotation = true;

	// Create the Camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

void APuzzlePawn::BeginPlay()
{
	Super::BeginPlay();
	// Add a random initial offset
	/*OnMouseDragX(FMath::RandRange(0, 180));
	OnMouseDragY(FMath::RandRange(0, 180));*/
	SpringArm->SetWorldRotation(FRotator(FMath::RandRange(0, 180), 0, FMath::RandRange(0, 180)));
	CanRotate = true;
}

void APuzzlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the mouse input axis for camera rotation
	PlayerInputComponent->BindAxis("MouseX", this, &APuzzlePawn::OnMouseDragX);
	PlayerInputComponent->BindAxis("MouseY", this, &APuzzlePawn::OnMouseDragY);
}

void APuzzlePawn::OnMouseDragX(float AxisValue)
{
	if (!CanRotate) return;

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
		{
			UE_LOG(LogTemp, Warning, TEXT("OnMouseDragX: %f"), AxisValue);
			float DeltaTime = GetWorld()->GetDeltaSeconds();

			// Apply the mouse movement to the SpringArm rotation
			FRotator NewRotation = SpringArm->GetComponentRotation();
			NewRotation.Yaw += AxisValue;

			// Set the new rotation for the SpringArm
			SpringArm->SetWorldRotation(NewRotation);
		}
	}
}

void APuzzlePawn::OnMouseDragY(float AxisValue)
{
	if (!CanRotate) return;

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
		{
			UE_LOG(LogTemp, Warning, TEXT("OnMouseDragY: %f"), AxisValue);
			float DeltaTime = GetWorld()->GetDeltaSeconds();
			// Apply the mouse movement to the SpringArm rotation
			FRotator NewRotation = SpringArm->GetComponentRotation();
			NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch - AxisValue, -80.0f, 80.0f);

			// Set the new rotation for the SpringArm
			SpringArm->SetWorldRotation(NewRotation);
			UE_LOG(LogTemp, Warning, TEXT("SpringArm Rotation: %s"), *NewRotation.ToString());
		}
	}
}


