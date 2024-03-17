// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponentPool.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "ProjectMPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UProjectMInputConfig;
class UProjectMAbilitySystemComponent;
class USplineComponent;
class IHighlightable;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AProjectMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProjectMPlayerController();

	virtual void Tick(float DeltaSeconds) override;
	virtual void PlayerTick(float DeltaTime) override;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UProjectMInputConfig* InputConfig;

	UPROPERTY()
	TObjectPtr<UProjectMAbilitySystemComponent> ProjectMAbilitySystemComponent;

	UProjectMAbilitySystemComponent* GetAbilitySystemComponent();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;
	UNiagaraComponent* ClickParticle;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed


	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void FindPathWithNavMesh();
	void AbilityInputTagHeld(FGameplayTag InputTag);

	bool bAutoRunning = false;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius;
	bool bTargeting = false;

	void AutoRun();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent>Spline;

	void CursorTrace();
	IHighlightable* ThisActor;
	IHighlightable* LastActor;
};


