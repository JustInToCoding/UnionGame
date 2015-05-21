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
	UFUNCTION(BlueprintPure, Category = Inventory)
		static UCraftingManager* getInstance();

	TArray<FEntry*> craftItem(FString ID);
	TArray<FEntry*> getAllCraftable();
	bool canCraft(Recipe recipe);

private:
	UInventory* inventory;
	TArray<Recipe*> recipes;
	void loadRecipes();
	
};
