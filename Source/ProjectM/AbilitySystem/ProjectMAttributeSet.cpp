// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMAttributeSet.h"
#include "Net/UnrealNetwork.h"

UProjectMAttributeSet::UProjectMAttributeSet()
{
	InitHealth(300.0f);
	InitMaxHealth(600.0f);
	InitMana(200.0f);
	InitMaxMana(300.0f);
	InitAttackDamage(50.0f);
	InitAbilityPower(50.0f);
	InitAttackSpeed(0.6f);
	InitMovementSpeed(300.0f);
	InitArmor(50.0f);
	InitMagicResist(50.0f);
	InitCriticalChance(0.0f);
	InitCriticalDamage(1.5f);
}

void UProjectMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, AbilityPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MagicResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, CriticalDamage, COND_None, REPNOTIFY_Always);
}

void UProjectMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, Health, OldHealth);
}

void UProjectMAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, MaxHealth, OldMaxHealth);
}

void UProjectMAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, Mana, OldMana);
}

void UProjectMAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, MaxMana, OldMaxMana);
}

void UProjectMAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, AttackDamage, OldAttackDamage);
}

void UProjectMAttributeSet::OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, AbilityPower, OldAbilityPower);
}

void UProjectMAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UProjectMAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UProjectMAttributeSet::OnRep_CriticalChance(const FGameplayAttributeData& OldCriticalChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, CriticalChance, OldCriticalChance);
}

void UProjectMAttributeSet::OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, CriticalChance, OldCriticalDamage);
}

void UProjectMAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, Armor, OldArmor);
}

void UProjectMAttributeSet::OnRep_MagicResist(const FGameplayAttributeData& OldMagicResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, MagicResist, OldMagicResist);
}

