// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MerinoGameplayAbilities : ModuleRules
{
	public MerinoGameplayAbilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "GameplayAbilities" });
	}
}
