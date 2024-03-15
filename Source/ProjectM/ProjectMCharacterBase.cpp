// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMCharacterBase.h"

UAbilitySystemComponent* AProjectMCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AProjectMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectMCharacterBase::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributeSet);
	
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle =  GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributeSet, 1.f, EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

AProjectMCharacterBase::AProjectMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

