// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMUserWidget.h"

void UProjectMUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();	
}

