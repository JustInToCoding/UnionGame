// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnionGame.h"

#include "MyGameResources.h"

class FUnionGameModule : public FDefaultGameModuleImpl
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called when GameModule is loaded, load any resources game may need here
	virtual void StartupModule() override
	{
		//Hot reload hack
		FSlateStyleRegistry::UnRegisterSlateStyle(FMyUIResources::GetStyleName());
		/*Loads resources and registers them with Slate*/
		/*Do this before trying to use resources*/
		FMyUIResources::Initialize();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called when GameModule is unloaded, before shutdown, unload resources/cleanup here
	virtual void ShutdownModule() override
	{
		/*Unregister resources/styles with Slate, cleanup, free memory*/
		FMyUIResources::Shutdown();

		/*Cleanup/free any resources here*/
	}

};

IMPLEMENT_PRIMARY_GAME_MODULE(FUnionGameModule, UnionGame, "UnionGame");
