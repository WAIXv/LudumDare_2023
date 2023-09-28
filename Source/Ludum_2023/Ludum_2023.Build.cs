// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ludum_2023 : ModuleRules
{
	public Ludum_2023(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" ,"AIModule", "GameplayTasks"});
	}
}
