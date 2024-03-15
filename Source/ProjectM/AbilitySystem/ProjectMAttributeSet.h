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

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties()
	{
	}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	const UAbilitySystemComponent* SourceASC;

	UPROPERTY()
	AActor* SourceAvatarActor;

	UPROPERTY()
	AController* SourceController;

	UPROPERTY()
	ACharacter* SourceCharacter;

	UPROPERTY()
	const UAbilitySystemComponent* TargetASC;

	UPROPERTY()
	AActor* TargetAvatarActor;

	UPROPERTY()
	AController* TargetController;

	UPROPERTY()
	ACharacter* TargetCharacter;
};

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

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/* Defensive */
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

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HealthRegenP5, Category = "Vitality")
	FGameplayAttributeData HealthRegenP5;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, HealthRegenP5);

	UFUNCTION()
	void OnRep_HealthRegenP5(const FGameplayAttributeData& OldHealthRegenP5) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Tenacity, Category = "Vitality")
	FGameplayAttributeData Tenacity;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, Tenacity);

	UFUNCTION()
	void OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_SlowResist, Category = "Vitality")
	FGameplayAttributeData SlowResist;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, SlowResist);

	UFUNCTION()
	void OnRep_SlowResist(const FGameplayAttributeData& OldSlowResist) const;

	
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
	
	/* Offensive */
	
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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LifeSteal, Category = "Power")
	FGameplayAttributeData LifeSteal;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, LifeSteal);

	UFUNCTION()
	void OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPenetration, Category = "Power")
	FGameplayAttributeData MagicPenetration;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, MagicPenetration);

	UFUNCTION()
	void OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Power")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, ArmorPenetration);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegenP5, Category = "Vitality")
	FGameplayAttributeData ManaRegenP5;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, ManaRegenP5);

	UFUNCTION()
	void OnRep_ManaRegenP5(const FGameplayAttributeData& OldManaRegenP5) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackRange, Category = "Power")
	FGameplayAttributeData AttackRange;
	ATTRIBUTE_ACCESSORS(UProjectMAttributeSet, AttackRange);

	UFUNCTION()
	void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const;
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties) const;
};
