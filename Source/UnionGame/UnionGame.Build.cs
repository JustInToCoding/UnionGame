// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnionGame : ModuleRules
{
	public UnionGame(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        // Add Json Modules
        PublicDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities" });

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

	}
}
