// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ProjectMAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTM_API UProjectMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UProjectMAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vitality")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, Health);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth, Category = "Vitality")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vitality")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, Mana);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vitality")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackDamage, Category = "Power")
	FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, AttackDamage);

	UFUNCTION()
	void OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AbilityPower, Category = "Power")
	FGameplayAttributeData AbilityPower;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, AbilityPower);

	UFUNCTION()
	void OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Power")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, AttackSpeed);
	
	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Power")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, MovementSpeed);

	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalChance, Category = "Power")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, CriticalChance);

	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& OldCriticalChance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalDamage, Category = "Power")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, CriticalDamage);

	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Defense")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, Armor);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResist, Category = "Defense")
	FGameplayAttributeData MagicResist;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, MagicResist);

	UFUNCTION()
	void OnRep_MagicResist(const FGameplayAttributeData& OldMagicResist) const;
};
