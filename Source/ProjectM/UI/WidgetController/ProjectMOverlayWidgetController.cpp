// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMOverlayWidgetController.h"
#include "ProjectM/AbilitySystem/ProjectMAttributeSet.h"

void UProjectMOverlayWidgetController::BroadcastInitialValues()
{
	if (const UProjectMAttributeSet* ProjectMAttributeSet = CastChecked<UProjectMAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(ProjectMAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(ProjectMAttributeSet->GetMaxHealth());
		OnManaChanged.Broadcast(ProjectMAttributeSet->GetMana());
		OnMaxManaChanged.Broadcast(ProjectMAttributeSet->GetMaxMana());
		OnAttackPowerChanged.Broadcast(ProjectMAttributeSet->GetAttackPower());
		OnDefenseChanged.Broadcast(ProjectMAttributeSet->GetDefense());
		OnMovementSpeedChanged.Broadcast(ProjectMAttributeSet->GetMovementSpeed());
		OnAttackSpeedChanged.Broadcast(ProjectMAttributeSet->GetAttackSpeed());
		OnCriticalChanceChanged.Broadcast(ProjectMAttributeSet->GetCriticalChance());
	}
}

void UProjectMOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UProjectMAttributeSet* ProjectMAttributeSet = CastChecked<UProjectMAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetHealthAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetManaAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::MaxManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetAttackPowerAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::AttackPowerChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetDefenseAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::DefenseChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetMovementSpeedAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::MovementSpeedChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetAttackSpeedAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::AttackSpeedChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetCriticalChanceAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::CriticalChanceChanged);
}

void UProjectMOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::AttackPowerChanged(const FOnAttributeChangeData& Data) const
{
	OnAttackPowerChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::DefenseChanged(const FOnAttributeChangeData& Data) const
{
	OnDefenseChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::MovementSpeedChanged(const FOnAttributeChangeData& Data) const
{
	OnMovementSpeedChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::AttackSpeedChanged(const FOnAttributeChangeData& Data) const
{
	OnAttackSpeedChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::CriticalChanceChanged(const FOnAttributeChangeData& Data) const
{
	OnCriticalChanceChanged.Broadcast(Data.NewValue);
}