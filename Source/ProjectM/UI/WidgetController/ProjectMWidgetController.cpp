// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMWidgetController.h"

void UProjectMWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams)
{
	PlayerController = InWidgetControllerParams.PlayerController;
	PlayerState = InWidgetControllerParams.PlayerState;
	AbilitySystemComponent = InWidgetControllerParams.AbilitySystemComponent;
	AttributeSet = InWidgetControllerParams.AttributeSet;
}

void UProjectMWidgetController::BroadcastInitialValues()
{
}

void UProjectMWidgetController::BindCallbacksToDependencies()
{
}
