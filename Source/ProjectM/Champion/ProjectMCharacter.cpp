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
#include "ProjectM/Player/ProjectMPlayerController.h"
#include "ProjectM/Player/ProjectMPlayerState.h"
#include "ProjectM/UI/Widget/ProjectMUserWidget.h"
#include "ProjectM/UI/HUD/ProjectMHUD.h"
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

	// Create health bar widget
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);

	HealthBarWidgetComponent->SetWidgetClass(HealthBarWidgetClass);
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawSize(FVector2D(100, 25));
	HealthBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	HealthBarWidgetComponent->SetVisibility(true);

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
}

void AProjectMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
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

	// if not server
	
	check(IsValid(HealthBarWidgetComponent->GetWidget()));

	 UUserWidget* Widget = HealthBarWidgetComponent->GetWidget();
	UProjectMUserWidget* ProjectMUserWidget = Cast<UProjectMUserWidget>(Widget);

	AProjectMPlayerController* ProjectMPlayerController = Cast<AProjectMPlayerController>(GetController());
	if (ProjectMPlayerController == nullptr) {
		return;
	}
	
	if (AProjectMHUD* ProjectMHUD = Cast<AProjectMHUD>(ProjectMPlayerController->GetHUD())) {
		UProjectMOverlayWidgetController* WidgetController = ProjectMHUD->GetOverlayWidgetController(FWidgetControllerParams(ProjectMPlayerController, GetPlayerState(), AbilitySystemComponent, AttributeSet));
		ProjectMUserWidget->SetWidgetController(WidgetController);
		WidgetController->BroadcastInitialValues();
	}
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
