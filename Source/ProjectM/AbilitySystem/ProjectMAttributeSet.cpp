// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

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
	InitLifeSteal(0.0f);
	InitMagicPenetration(0.0f);
	InitArmorPenetration(0.0f);
	InitTenacity(0.0f);
	InitSlowResist(0.0f);
	InitHealthRegenP5(5.0f);
	InitManaRegenP5(5.0f);
	InitAttackRange(150.0f);
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
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, LifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, MagicPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, SlowResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, HealthRegenP5, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, ManaRegenP5, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectMAttributeSet, AttackRange, COND_None, REPNOTIFY_Always);
}

void UProjectMAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
	else if (Attribute == GetMaxHealthAttribute() || Attribute == GetMaxManaAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

void UProjectMAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UProjectMAttributeSet::OnRep_ManaRegenP5(const FGameplayAttributeData& OldManaRegenP5) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, ManaRegenP5, OldManaRegenP5);
}

void UProjectMAttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, AttackRange, OldAttackRange);
}

void UProjectMAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
                                                FEffectProperties& EffectProperties) const
{
const FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	EffectProperties.EffectContextHandle = Context;

	const UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	EffectProperties.SourceASC = Source;

	if (IsValid(Source) && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* Avatar = Source->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceAvatarActor = Avatar;

		const AController* Controller = Source->AbilityActorInfo->PlayerController.Get();
		EffectProperties.SourceController = const_cast<AController*>(Controller);

		if (Controller == nullptr && Avatar != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Avatar))
			{
				Controller = Pawn->GetController();
				EffectProperties.SourceController = const_cast<AController*>(Controller);
			}
		}

		if (Controller)
		{
			ACharacter* Character = Cast<ACharacter>(Controller->GetPawn());
			EffectProperties.SourceCharacter = Character;
		}
		
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetController->GetPawn());
	}
	
	
}


void UProjectMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Properties;
	SetEffectProperties(Data, Properties);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		SetMaxHealth(FMath::Max(GetMaxHealth(), 0.0f));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxManaAttribute())
	{
		SetMaxMana(FMath::Max(GetMaxMana(), 0.0f));
	}

}

void UProjectMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, Health, OldHealth);
}

void UProjectMAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, MaxHealth, OldMaxHealth);
}

void UProjectMAttributeSet::OnRep_HealthRegenP5(const FGameplayAttributeData& OldHealthRegenP5) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, HealthRegenP5, OldHealthRegenP5);
}

void UProjectMAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, Tenacity, OldTenacity);
}

void UProjectMAttributeSet::OnRep_SlowResist(const FGameplayAttributeData& OldSlowResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, SlowResist, OldSlowResist);
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

void UProjectMAttributeSet::OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, LifeSteal, OldLifeSteal);
}

void UProjectMAttributeSet::OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, MagicPenetration, OldMagicPenetration);
}

void UProjectMAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, Armor, OldArmor);
}

void UProjectMAttributeSet::OnRep_MagicResist(const FGameplayAttributeData& OldMagicResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectMAttributeSet, MagicResist, OldMagicResist);
}


