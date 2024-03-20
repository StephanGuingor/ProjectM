// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectM/AbilitySystem/Abilities/ProjectMGameplayAbility.h"
#include "ProjectMProjectileSpell.generated.h"

class AProjectMProyectile;
/**
 * 
 */
UCLASS()
class PROJECTM_API UProjectMProjectileSpell : public UProjectMGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectMProyectile> ProjectileClass;
};
