////////////////////////////////////////////////////////////////////////////////////////////////////
/////Date: April 2, 2014
/////Author: Bleakwise
/////File: MyGameResources.cpp

#include "UnionGame.h"
#include "SlateGameResources.h"
#include "MyGameResources.h"

TSharedPtr<FSlateStyleSet> FMyUIResources::MyUIResources = NULL;

void FMyUIResources::Initialize()
{
	if (!MyUIResources.IsValid())
	{
		MyUIResources = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MyUIResources);
	}
}

const FSlateStyleSet& FMyUIResources::GetSlateStyleResources()
{
	return *MyUIResources;
}

FName FMyUIResources::GetStyleName()
{
	static FName StyleSetName(TEXT("UnionGameStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::GameContentDir() / RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::GameContentDir() / RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::GameContentDir() / RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / RelativePath + TEXT(".otf"), __VA_ARGS__ )


TSharedRef<class FSlateStyleSet> FMyUIResources::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FMyUIResources::GetStyleName(), "/Game/UI", "/Game/UI");
	FSlateStyleSet & Style = StyleRef.Get();
	
	TArray<Item*> Items = UItemManager::getInstance()->getItems();

	for (Item* Item : Items)
	{
		// Load the item icons to be used for displaying when a user is talking
		FName Name = FName(*FString("UnionGame." + Item->getID()));
		Style.Set(Name, new IMAGE_BRUSH(Item->getSprite(), FVector2D(128, 128)));
	}

	// Load the HUD image
	Style.Set(FName(*FString("UnionGame.HUD")), new IMAGE_BRUSH("/UI/Images/HUD", FVector2D(815, 204)));
	Style.Set(FName(*FString("UnionGame.Stamina")), new IMAGE_BRUSH("/UI/Images/Stamina", FVector2D(140, 204)));
	Style.Set(FName(*FString("UnionGame.Health")), new IMAGE_BRUSH("/UI/Images/Health", FVector2D(140, 204)));
	Style.Set(FName(*FString("UnionGame.MenuBackground")), new IMAGE_BRUSH("/UI/Images/MenuBackground", FVector2D(634, 813)));
	Style.Set(FName(*FString("UnionGame.MenuButton")), new IMAGE_BRUSH("/UI/Images/Button", FVector2D(138, 51)));
	Style.Set(FName(*FString("UnionGame.Transparent")), new IMAGE_BRUSH("", FVector2D(1, 1), FLinearColor(0,0,0,0)));
	

	return StyleRef;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

/*reloads textures used by slate renderer*/
void FMyUIResources::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}


/*Unregister resources/styles with Slate, cleanup, free memory*/
void FMyUIResources::Shutdown()
{
	//Unregister *MyUIResources with Slate
	FSlateStyleRegistry::UnRegisterSlateStyle(*MyUIResources);

	//Debugging
	ensure(MyUIResources.IsUnique());

	//Removes reference to resources, decrements refcount, destroys resources if refcount=0
	//Do this to all SharedPtrs on Shutdown() or SomethingSimilar() to avoid memory leak
	MyUIResources.Reset();
}