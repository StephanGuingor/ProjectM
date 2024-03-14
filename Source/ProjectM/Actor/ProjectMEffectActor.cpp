// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

// Sets default values
AProjectMEffectActor::AProjectMEffectActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AProjectMEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectMEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> EffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC == nullptr) return;

	FGameplayEffectContextHandle EffectContextHandle= TargetASC->MakeEffectContext();

	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =  TargetASC->MakeOutgoingSpec(EffectClass, 1.f,EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
