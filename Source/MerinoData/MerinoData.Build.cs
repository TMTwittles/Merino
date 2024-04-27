// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MerinoData : ModuleRules
{
	public MerinoData(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
	}
}
