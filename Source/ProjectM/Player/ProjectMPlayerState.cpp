// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMPlayerState.h"
#include "ProjectM/AbilitySystem/ProjectMAttributeSet.h"
#include "ProjectM/AbilitySystem/ProjectMAbilitySystemComponent.h"

AProjectMPlayerState::AProjectMPlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UProjectMAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UProjectMAttributeSet>("AttributeSet");
}