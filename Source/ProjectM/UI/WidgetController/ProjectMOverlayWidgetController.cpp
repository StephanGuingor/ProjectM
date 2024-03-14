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
		OnAttackDamageChanged.Broadcast(ProjectMAttributeSet->GetAttackDamage());
		OnAbilityPowerChanged.Broadcast(ProjectMAttributeSet->GetAbilityPower());
		OnArmorChanged.Broadcast(ProjectMAttributeSet->GetArmor());
		OnMagicResistChanged.Broadcast(ProjectMAttributeSet->GetMagicResist());
		OnMovementSpeedChanged.Broadcast(ProjectMAttributeSet->GetMovementSpeed());
		OnAttackSpeedChanged.Broadcast(ProjectMAttributeSet->GetAttackSpeed());
		OnCriticalChanceChanged.Broadcast(ProjectMAttributeSet->GetCriticalChance());
		OnCriticalDamageChanged.Broadcast(ProjectMAttributeSet->GetCriticalDamage());
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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetAttackDamageAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::AttackDamageChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetAbilityPowerAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::AbilityPowerChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetArmorAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::ArmorChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetMagicResistAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::MagicResistChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetMovementSpeedAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::MovementSpeedChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetAttackSpeedAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::AttackSpeedChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetCriticalChanceAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::CriticalChanceChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjectMAttributeSet->GetCriticalDamageAttribute()).AddUObject(this, &UProjectMOverlayWidgetController::CriticalDamageChanged);
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

void UProjectMOverlayWidgetController::AttackDamageChanged(const FOnAttributeChangeData& Data) const
{
	OnAttackDamageChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::AbilityPowerChanged(const FOnAttributeChangeData& Data) const
{
	OnAbilityPowerChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::ArmorChanged(const FOnAttributeChangeData& Data) const
{
	OnArmorChanged.Broadcast(Data.NewValue);
}

void UProjectMOverlayWidgetController::MagicResistChanged(const FOnAttributeChangeData& Data) const
{
	OnMagicResistChanged.Broadcast(Data.NewValue);
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

void UProjectMOverlayWidgetController::CriticalDamageChanged(const FOnAttributeChangeData& Data) const
{
	OnCriticalDamageChanged.Broadcast(Data.NewValue);
}
