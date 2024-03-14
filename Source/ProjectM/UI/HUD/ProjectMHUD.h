// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectMHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UProjectMUserWidget;
class UProjectMOverlayWidgetController;

/**
 * 
 */
UCLASS()
class PROJECTM_API AProjectMHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UProjectMUserWidget> OverlayWidget;

	UProjectMOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams);

	void InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState, UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet);
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UProjectMUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UProjectMOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UProjectMOverlayWidgetController> OverlayWidgetControllerClass;
};
