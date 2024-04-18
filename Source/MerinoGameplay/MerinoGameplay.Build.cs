// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MerinoGameplay : ModuleRules
{
	public MerinoGameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","MerinoStatics" });
	}
}
