// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class C_Action : ModuleRules
{
	public C_Action(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara", "HairStrandsCore","GeometryCollectionEngine","Niagara","UMG", "AIModule" });
	}
}
