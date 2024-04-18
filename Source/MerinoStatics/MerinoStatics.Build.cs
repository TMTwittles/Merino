// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class MerinoStatics : ModuleRules
{
	public MerinoStatics(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine"});
	}
}