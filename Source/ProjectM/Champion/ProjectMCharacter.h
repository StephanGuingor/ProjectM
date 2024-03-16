// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"

#include "ProjectM/Champion/ProjectMCharacterBase.h"
#include "ProjectMCharacter.generated.h"

UCLASS(Blueprintable)
class AProjectMCharacter : public AProjectMCharacterBase
{
	GENERATED_BODY()

public:
	AProjectMCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual int32 GetPlayerLevel() override;
protected:
	void BeginPlay() override;

	UPROPERTY()
	class UProjectMFloatingStatusBarWidget* UIFloatingStatusBar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UProjectMFloatingStatusBarWidget> UIFloatingStatusBarClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UWidgetComponent* UIFloatingStatusBarComponent;
	
	// Creates and initializes the floating status bar for heroes.
	// Safe to call many times because it checks to make sure it only executes once.
	UFUNCTION()
	void InitializeFloatingStatusBar();
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	void InitAbilityActorInfo();
};

