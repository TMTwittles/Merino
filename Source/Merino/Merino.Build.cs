// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Merino : ModuleRules
{
	public Merino(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "MerinoGameplay", "MerinoGameplayAbilities", "GameplayAbilities"});
		PrivateDependencyModuleNames.AddRange(new string[] { "MerinoStatics", "InputCore", "EnhancedInput" });
	}
}
