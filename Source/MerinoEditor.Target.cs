// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MerinoEditorTarget : TargetRules
{
	public MerinoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;

		// Modules
		ExtraModuleNames.Add("Merino");
		ExtraModuleNames.Add("MerinoGameplay");
		ExtraModuleNames.Add("MerinoStatics");
	}
}
