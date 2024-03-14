// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectMCharacter.h"

#include "AbilitySystem/ProjectMAbilitySystemComponent.h"
#include "AbilitySystem/ProjectMAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Player/ProjectMPlayerController.h"
#include "Player/ProjectMPlayerState.h"
#include "ProjectM/UI/HUD/ProjectMHUD.h"

AProjectMCharacter::AProjectMCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 1280.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProjectMCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AProjectMCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init on server

	if(AProjectMPlayerState* APlayerState = GetPlayerState<AProjectMPlayerState>() )
	{
		APlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(APlayerState, this);
		AbilitySystemComponent = APlayerState->GetAbilitySystemComponent();
		AttributeSet = APlayerState->GetAttributeSet();
		
		if(AProjectMPlayerController* ProjectMPlayerController = Cast<AProjectMPlayerController>(GetController()))
		{
			if (AProjectMHUD* ProjectMHUD = Cast<AProjectMHUD>(ProjectMPlayerController->GetHUD()))
			{
				ProjectMHUD->InitOverlay(ProjectMPlayerController, APlayerState, AbilitySystemComponent, AttributeSet);
			}
		}	
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PossessedBy"));
	}
}

void AProjectMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// get the player state
	if(AProjectMPlayerState* APlayerState = GetPlayerState<AProjectMPlayerState>() )
	{
		APlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(APlayerState, this);
		AbilitySystemComponent = APlayerState->GetAbilitySystemComponent();
		AttributeSet = APlayerState->GetAttributeSet();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnRep_PlayerState"));
	}
}
