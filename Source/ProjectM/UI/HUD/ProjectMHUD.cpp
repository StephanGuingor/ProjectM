// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMHUD.h"

#include "ProjectM/UI/Widget/ProjectMUserWidget.h"
#include "ProjectM/UI/WidgetController/ProjectMWidgetController.h"
#include "ProjectM/UI/WidgetController/ProjectMOverlayWidgetController.h"

UProjectMOverlayWidgetController* AProjectMHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& InWidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UProjectMOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(InWidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		
		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void AProjectMHUD::InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState,
	UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set in %s"), *GetName());
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set in %s"), *GetName());
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UProjectMUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(InPlayerController, InPlayerState, InAbilitySystemComponent, InAttributeSet);

	UProjectMOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}

