// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Workshop4 : ModuleRules
{
	public Workshop4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
