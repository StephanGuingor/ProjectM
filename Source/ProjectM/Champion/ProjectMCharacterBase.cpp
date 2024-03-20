// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "ProjectM/ProjectM.h"
#include "ProjectM/AbilitySystem/ProjectMAbilitySystemComponent.h"

AProjectMCharacterBase::AProjectMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
}

UAbilitySystemComponent* AProjectMCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AProjectMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

FVector AProjectMCharacterBase::GetCombatSocketLocation()
{
	return GetActorLocation() + GetActorForwardVector() * 100.f;
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

void AProjectMCharacterBase::AddCharacterAbilities()
{
	UProjectMAbilitySystemComponent* AbilitySystem = CastChecked<UProjectMAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	AbilitySystem->AddCharacterAbilities(StartupAbilities);	
}

