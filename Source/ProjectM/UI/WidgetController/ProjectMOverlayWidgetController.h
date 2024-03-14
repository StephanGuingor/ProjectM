// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectM/UI/WidgetController/ProjectMWidgetController.h"
#include "ProjectMOverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackDamageChangedSignature, float, NewAttackDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityPowerChangedSignature, float, NewAbilityPower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArmorChangedSignature, float, NewArmor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagicResistChangedSignature, float, NewMagicResist);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementSpeedChangedSignature, float, NewMoveSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackSpeedChangedSignature, float, NewCastAttackSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCriticalChanceChangedSignature, float, NewCriticalChance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCriticalDamageChangedSignature, float, NewCriticalDamage);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTM_API UProjectMOverlayWidgetController : public UProjectMWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttackDamageChangedSignature OnAttackDamageChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAbilityPowerChangedSignature OnAbilityPowerChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnArmorChangedSignature OnArmorChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMagicResistChangedSignature OnMagicResistChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMovementSpeedChangedSignature OnMovementSpeedChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttackSpeedChangedSignature OnAttackSpeedChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnCriticalChanceChangedSignature OnCriticalChanceChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnCriticalDamageChangedSignature OnCriticalDamageChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	void AttackDamageChanged(const FOnAttributeChangeData& Data) const;
	void AbilityPowerChanged(const FOnAttributeChangeData& Data) const;
	void ArmorChanged(const FOnAttributeChangeData& Data) const;
	void MagicResistChanged(const FOnAttributeChangeData& Data) const;
	void MovementSpeedChanged(const FOnAttributeChangeData& Data) const;
	void AttackSpeedChanged(const FOnAttributeChangeData& Data) const;
	void CriticalChanceChanged(const FOnAttributeChangeData& Data) const;
	void CriticalDamageChanged(const FOnAttributeChangeData& Data) const;
};
