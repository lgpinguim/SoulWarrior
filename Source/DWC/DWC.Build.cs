// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DWC : ModuleRules
{
	public DWC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {"Slate", "SlateCore"});
	}
}
