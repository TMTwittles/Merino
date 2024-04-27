// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MerinoTarget : TargetRules
{
	public MerinoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;

		// Modules
		ExtraModuleNames.Add("Merino");
		ExtraModuleNames.Add("MerinoGameplay");
		ExtraModuleNames.Add("MerinoStatics");
	}
}
