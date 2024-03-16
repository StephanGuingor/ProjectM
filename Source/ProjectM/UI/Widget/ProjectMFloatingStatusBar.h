// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectMFloatingStatusBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API UProjectMFloatingStatusBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	class AProjectMCharacterBase* OwningCharacter;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthPercentage(float HealthPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPercentage(float ManaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCharacterName(const FText& NewName);

	// Create event for when health bar is set
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void OnWidgetSet();
};