// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tdl_game_sequel : ModuleRules
{
	public Tdl_game_sequel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
