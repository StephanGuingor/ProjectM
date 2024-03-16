// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectMInputConfig.h"

const UInputAction* UProjectMInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                           bool bLogNotFound) const
{
	for (const FProjectMInputAction& InputAction : AbilityInputActions)
	{
		if (InputAction.InputAction && InputAction.InputTag == InputTag)
		{
			return InputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("No input action found for tag %s in ability %s"), *InputTag.ToString(), *GetName());
	}
	
	return nullptr;
}

