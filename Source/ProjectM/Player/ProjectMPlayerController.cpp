// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectMPlayerController.h"

#include <functional>

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectM/Champion/ProjectMCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Math/Vector.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AProjectMPlayerController::AProjectMPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AProjectMPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AProjectMPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AProjectMPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AProjectMPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AProjectMPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AProjectMPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AProjectMPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AProjectMPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AProjectMPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AProjectMPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectMPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn == nullptr)
	{
		return;
	}
	
	if (UE::Geometry::Distance(ControlledPawn->GetActorLocation(), CachedDestination) >= 110)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal() * 300;
		
		FVector CurrentDirection = ControlledPawn->GetActorForwardVector().GetSafeNormal();
		FVector CachedDestinationNormal = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();

		float angle = FVector::DotProduct(CurrentDirection, CachedDestinationNormal);

		ACharacter* character = GetCharacter();
		UCharacterMovementComponent* characterMovement = character->GetCharacterMovement();
		
		if (angle > 0.5)
		{
			characterMovement->RotationRate = FRotator(0.f, 600.f, 0.f);
		}
		else
		{
			characterMovement->RotationRate = FRotator(0.f, 1500.f, 0.f);
		}
		
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AProjectMPlayerController::OnInputStarted()
{
	StopMovement();
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	// if (bHitSuccessful)
	// {
	// 	CachedDestination = Hit.Location;
	// 	
	// 	if (ClickParticle != nullptr && IsValid(ClickParticle))
	// 	{
	// 		ClickParticle->DestroyInstance();
	// 		ClickParticle = nullptr;
	// 	}
	// 	ClickParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination,
	// 	                                                               FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
	// 	                                                               true, true, ENCPoolMethod::None, true);
	// }
	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
}




// Triggered every frame when the input is held down
void AProjectMPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		// ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
		// UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}
}

void AProjectMPlayerController::OnSetDestinationReleased()
{
	// // If it was a short press
	// if (FollowTime <= ShortPressThreshold)
	// {
	// 	// We move there and spawn some particles
	// 	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	// 	
	// }
	//
	// FollowTime =

	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}
	
	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	//
	// UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
}

// Triggered every frame when the input is held down
void AProjectMPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AProjectMPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
