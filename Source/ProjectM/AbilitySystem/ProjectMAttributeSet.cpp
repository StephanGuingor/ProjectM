// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMAttributeSet.h"
#include "Net/UnrealNetwork.h"

UProjectMAttributeSet::UProjectMAttributeSet()
{
	InitHealth(600.0f);
	InitMaxHealth(600.0f);
	InitMana(300.0f);
	InitMaxMana(300.0f);
	InitAttackPower(50.0f);
	InitAttackSpeed(0.6f);
	InitMovementSpeed(300.0f);
	InitDefense(50.0f);
	InitCriticalChance(0.05f);
}

void UProjectMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, CriticalChance, COND_None, REPNOTIFY_Always);
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

void UProjectMAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, AttackPower, OldAttackPower);
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

void UProjectMAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, Defense, OldDefense);
}