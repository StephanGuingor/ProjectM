// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectMEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class PROJECTM_API AProjectMEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProjectMEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> EffectClass);
};
