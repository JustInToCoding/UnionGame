// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Recipe.h"
#include "CraftingManager.generated.h"

UCLASS(Blueprintable)
class UNIONGAME_API UCraftingManager : public UObject
{
	GENERATED_BODY()
	
	UCraftingManager(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
	~UCraftingManager();
public:
	UFUNCTION(BlueprintPure, Category = Crafting)
		static UCraftingManager* getInstance();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void craftItem(FString id);

	UFUNCTION(BlueprintCallable, Category = Crafting)
	TArray<FString> getAllCraftable();

	UFUNCTION(BlueprintCallable, Category = Crafting)
	bool canCraft(FString id);

private:
	UInventory* inventory;
	TArray<Recipe*> recipes;
	void loadRecipes();
	Recipe* getRecipe(FString id);

};
