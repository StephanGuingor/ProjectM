// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectM/AbilitySystem/Abilities/ProjectMProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ProjectM/Actor/ProjectMProyectile.h"
#include "ProjectM/Interaction/CombatInterface.h"

void UProjectMProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UProjectMProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer)
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		FRotator LookAtRotation = (TargetLocation - SocketLocation).Rotation();
		LookAtRotation.Pitch = 0.0f;
		SpawnTransform.SetRotation(LookAtRotation.Quaternion());
		
		AProjectMProyectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectMProyectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		
		const FGameplayEffectSpecHandle SpecHandle = SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceAbilitySystemComponent->MakeEffectContext());
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
