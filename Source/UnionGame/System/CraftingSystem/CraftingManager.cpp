// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "CraftingManager.h"
#include "RecipeConverter.h"
#include "../../DynamicData/DDReg.h"

UCraftingManager* UCraftingManager::getInstance() {
	static UCraftingManager* instance = NewObject<UCraftingManager>();
	return instance;
}

UCraftingManager::UCraftingManager(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer){
	AddToRoot();
	UInventory* inventory = UInventory::getInstance();
	recipes.Init(0);
	loadRecipes();
}

UCraftingManager::~UCraftingManager(){}

void UCraftingManager::loadRecipes(){
	RecipeConverter* rc = RecipeConverter::getInstance();
	TArray<DDObject*> recipesRaw = DDReg::load(FPaths::GameDir() + "Recipes.json");

	for (int i = 0; i < recipesRaw.Num(); i++) {
		Recipe* recipe = static_cast<Recipe*>(recipesRaw[i]);

		recipes.Add(recipe);
	}
}

bool UCraftingManager::canCraft(Recipe recipe){
	TArray<FEntry*> needs = recipe.getNeeds();
	for (int i = 0; i < needs.Num(); i++){
		if (inventory->getAmount(needs[i]->id) < needs[i]->amount){
			return false;
		}
	}
	return true;
}

TArray<FEntry*> UCraftingManager::getAllCraftable(){
	TArray<FEntry*> ids;
	for (int i = 0; i < recipes.Num(); i++){
		TArray<FEntry*> gives = recipes[i]->getGives;
		for (int j = 0; j < gives.Num(); j++){
			ids.Add(gives[j]);
		}
	}
	return ids;
}

TArray<Item*> UCraftingManager::craftItem(FString ID){
	
}
