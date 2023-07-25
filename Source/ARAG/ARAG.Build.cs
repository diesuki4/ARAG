// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ARAG : ModuleRules
{
	public ARAG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
															"HeadMountedDisplay", "EnhancedInput", "NavigationSystem",
															"AIModule"});

		PublicIncludePaths.Add("ARAG/");

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });
	}
}
