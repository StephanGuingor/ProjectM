// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMAbilitySystemComponent.h"

void UProjectMAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UProjectMAbilitySystemComponent::EffectApplied);
}

void UProjectMAbilitySystemComponent::AddCharacterAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		// GiveAbility(AbilitySpec);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UProjectMAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                    const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);

	OnEffectAssetTags.Broadcast(AssetTags);

	for (const FGameplayTag& Tag : AssetTags)
	{
		// TODO: broadcast to UI
		GEngine->AddOnScreenDebugMessage(-1, 9.f, FColor::Blue, Tag.ToString());
	}
}
