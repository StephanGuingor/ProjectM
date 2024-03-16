// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectMCharacter.h"

#include "ProjectM/AbilitySystem/ProjectMAbilitySystemComponent.h"
#include "ProjectM/AbilitySystem/ProjectMAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectM/Player/ProjectMPlayerController.h"
#include "ProjectM/Player/ProjectMPlayerState.h"
#include "ProjectM/UI/Widget/ProjectMUserWidget.h"
#include "ProjectM/UI/HUD/ProjectMHUD.h"
#include "ProjectM/UI/Widget/ProjectMFloatingStatusBar.h"
#include "ProjectM/AbilitySystem/ProjectMAttributeSet.h"
#include "ProjectM/UI/WidgetController/ProjectMWidgetController.h"
#include "ProjectM/UI/WidgetController/ProjectMOverlayWidgetController.h"

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

	UIFloatingStatusBarComponent = CreateDefaultSubobject<UWidgetComponent>(FName("UIFloatingStatusBarComponent"));
	UIFloatingStatusBarComponent->SetupAttachment(RootComponent);
	UIFloatingStatusBarComponent->SetRelativeLocation(FVector(0, 0, 120));
	UIFloatingStatusBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	UIFloatingStatusBarComponent->SetDrawSize(FVector2D(500, 500));

	// UIFloatingStatusBarClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/GASShooter/UI/UI_FloatingStatusBar_Hero.UI_FloatingStatusBar_Hero_C"));
	// if (!UIFloatingStatusBarClass)
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("%s() Failed to find UIFloatingStatusBarClass. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	// }

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
	InitAbilityActorInfo();
	AddCharacterAbilities();
	InitializeFloatingStatusBar();
}

void AProjectMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();

	InitializeFloatingStatusBar();
}

int32 AProjectMCharacter::GetPlayerLevel()
{
	const AProjectMPlayerState* APlayerState = GetPlayerState<AProjectMPlayerState>();
	checkf(APlayerState, TEXT("APlayerState is null"));
	return APlayerState->GetPlayerLevel();
}

void AProjectMCharacter::BeginPlay()
{
	Super::BeginPlay();

	// check if is server authority
	if (!HasAuthority())
	{
		return;
	}

	AProjectMPlayerController* ProjectMPlayerController = Cast<AProjectMPlayerController>(GetController());
	if (ProjectMPlayerController == nullptr) {
		return;
	}

	InitializeFloatingStatusBar();
}

void AProjectMCharacter::InitAbilityActorInfo()
{
	AProjectMPlayerState* APlayerState = GetPlayerState<AProjectMPlayerState>() ;
	checkf(APlayerState, TEXT("APlayerState is null"));

	APlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(APlayerState, this);
	AbilitySystemComponent = APlayerState->GetAbilitySystemComponent();
	Cast<UProjectMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = APlayerState->GetAttributeSet();
	
	AProjectMPlayerController* ProjectMPlayerController = Cast<AProjectMPlayerController>(GetController());
	if (ProjectMPlayerController == nullptr)
	{
		return;
	}
	
	if (AProjectMHUD* ProjectMHUD = Cast<AProjectMHUD>(ProjectMPlayerController->GetHUD()))
	{
		ProjectMHUD->InitOverlay(ProjectMPlayerController, APlayerState, AbilitySystemComponent, AttributeSet);
	}

	InitializePrimaryAttributes();
}

void AProjectMCharacter::InitializeFloatingStatusBar()
{
	// Only create once
	if (UIFloatingStatusBar || !IsValid(AbilitySystemComponent))
	{
		return;
	}

	// Need a valid PlayerState
	if (!GetPlayerState())
	{
		return;
	}

	// Setup UI for Locally Owned Players only, not AI or the server's copy of the PlayerControllers
	AProjectMPlayerController* PC = Cast<AProjectMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->IsLocalPlayerController())
	{
		if (UIFloatingStatusBarClass)
		{
			UIFloatingStatusBar = CreateWidget<UProjectMFloatingStatusBarWidget>(PC, UIFloatingStatusBarClass);
			if (UIFloatingStatusBar && UIFloatingStatusBarComponent)
			{
				UIFloatingStatusBarComponent->SetWidget(UIFloatingStatusBar);

				UProjectMAttributeSet* AttributeSetBase = Cast<UProjectMAttributeSet>(AttributeSet);

				const FText CharacterName = FText::FromString("Ephyr");
				// Setup the floating status bar
				UIFloatingStatusBar->SetHealthPercentage(AttributeSetBase->GetHealth() / AttributeSetBase->GetMaxHealth());
				UIFloatingStatusBar->SetManaPercentage(AttributeSetBase->GetMana() / AttributeSetBase->GetMaxMana());
				UIFloatingStatusBar->OwningCharacter = this;
				UIFloatingStatusBar->SetCharacterName(CharacterName);
				UIFloatingStatusBar->OnWidgetSet();
			}
		}
	}

}
