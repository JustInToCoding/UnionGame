////////////////////////////////////////////////////////////////////////////////////////////////////
/////Date: April 2, 2014
/////Author: Bleakwise
/////File: MyGameResources.h

#pragma once

#include "System/ItemSystem/Item.h"
#include "System/ItemSystem/ItemManager.h"
#include "Slate.h"
#include "SlateGameResources.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/////Data Structure and Interface for maintaining SlateGameResources on Game to Game basis
class FMyUIResources
{
public:
	/*Loads resources and registers them with Slate*/
	/*Do this before trying to use resources*/
	static void Initialize();

	/*cleanup*/
	/*Do this when shutting down game module*/
	static void Shutdown();

	/*reloads textures used by slate renderer*/
	static void ReloadTextures();

	/*Give caller a pointer to our FSlateGameResources*/
	static const FSlateStyleSet & GetSlateStyleResources();

	/*Give caller the name of our ResourceSet*/
	static FName GetStyleName();

private:
	/*Creates resources*/
	static TSharedRef<class FSlateStyleSet> Create();

	/*Poitner to game resources, Initialize() before using*/
	static TSharedPtr<FSlateStyleSet> MyUIResources;

};