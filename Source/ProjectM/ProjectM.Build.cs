// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectM : ModuleRules
{
	public ProjectM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks"});
	}
}
