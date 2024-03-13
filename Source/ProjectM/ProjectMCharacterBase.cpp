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

AProjectMCharacterBase::AProjectMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}