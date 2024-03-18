// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectMPlayerController.h"

#include <functional>

#include "AbilitySystemBlueprintLibrary.h"
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
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Math/Vector.h"
#include "ProjectM/AbilitySystem/ProjectMAbilitySystemComponent.h"
#include "ProjectM/Input/ProjectMInputComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AProjectMPlayerController::AProjectMPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UProjectMInputConfig> InputConfigAsset(TEXT("/Game/Input/DA_TEST.DA_TEST"));
	InputConfig = InputConfigAsset.Object;
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	ShortPressThreshold = 0.5f;
	AutoRunAcceptanceRadius = 110.f;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
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

UProjectMAbilitySystemComponent* AProjectMPlayerController::GetAbilitySystemComponent()
{
	if (ProjectMAbilitySystemComponent == nullptr)
	{
		ProjectMAbilitySystemComponent = Cast<UProjectMAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return ProjectMAbilitySystemComponent;
}

void AProjectMPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UProjectMInputComponent* EnhancedInputComponent = CastChecked<UProjectMInputComponent>(InputComponent))
	{
		check(InputConfig);
		EnhancedInputComponent->BindAbilityActions(InputConfig, this, &AProjectMPlayerController::AbilityInputTagPressed, &AProjectMPlayerController::AbilityInputTagReleased, &AProjectMPlayerController::AbilityInputTagHeld);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectMPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AProjectMPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	if (bAutoRunning)
	{
		AutoRun();
	}
	
}

void AProjectMPlayerController::AutoRun()
{
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}


void AProjectMPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	Cast<IHighlightable>(CursorHit.GetActor());

	LastActor = ThisActor;
	ThisActor = Cast<IHighlightable>(CursorHit.GetActor());

	/**
	 * Line trace from cursor. There are serveral scenarios:
	 * A. LastActor is null and ThisActor is null
	 *	- Do nothing
	 * B. LastActor is null and ThisActor is not null
	 *	- Highlight ThisActor
	 *	C. LastActor is not null and ThisActor is null
	 *	- Unhighlight LastActor
	 *	D. LastActor is not null and ThisActor is not null, LastActor != ThisActor
	 *	- Unhighlight LastActor
	 *	- Highlight ThisActor
	 *	E. LastActor is not null and ThisActor is not null, LastActor == ThisActor
	 *	- Do nothing
	 */
	
	if (LastActor == nullptr && ThisActor != nullptr)
	{
		ThisActor->HighlightActor();
	}
	else if (LastActor != nullptr && ThisActor == nullptr)
	{
		LastActor->UnhighlightActor();
	}
	else if (LastActor != nullptr && ThisActor != nullptr && LastActor != ThisActor)
	{
		LastActor->UnhighlightActor();
		ThisActor->HighlightActor();
	}
}

void AProjectMPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("Input.RMB")))
	{
		if (GetAbilitySystemComponent())
		{
			GetAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	
	if (GetAbilitySystemComponent() == nullptr)
	{
		return;
	}

	bTargeting = ThisActor ? true : false;
	bAutoRunning = false;

	if (bTargeting)
	{
		if (GetAbilitySystemComponent())
		{
			GetAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}
}

void AProjectMPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	
}

void AProjectMPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("Input.RMB")))
	{
		if (GetAbilitySystemComponent())
		{
			GetAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	
	if (GetAbilitySystemComponent() == nullptr)
	{
		return;
	}

	bTargeting = ThisActor ? true : false;
	bAutoRunning = false;

	if (bTargeting)
	{
		
		if (GetAbilitySystemComponent())
		{
			GetAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
		
		return;
	}

	FindPathWithNavMesh();
	
}

void AProjectMPlayerController::FindPathWithNavMesh()
{
	
	if(CursorHit.bBlockingHit)
	{
		CachedDestination = CursorHit.Location;
		
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if(UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& Point : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), Point, 8, 8, FColor::Green, false, 2.f);
				}
				if (NavPath->PathPoints.Num() == 0)
				{
					return;
				}
				CachedDestination = NavPath->PathPoints.Last();
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}
