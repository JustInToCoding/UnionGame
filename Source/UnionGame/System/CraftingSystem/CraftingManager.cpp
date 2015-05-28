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

bool UCraftingManager::canCraft(FString id){
	Recipe* recipe = getRecipe(id);
	if (recipe != nullptr){
		TArray<FEntry*> needs = recipe->getNeeds();
		for (int i = 0; i < needs.Num(); i++){
			if (inventory->getAmount(needs[i]->id) < needs[i]->amount){
				return false;
			}
		}
		return true;
	}
	return false;
}

TArray<FString> UCraftingManager::getAllCraftable(){
	TArray<FString> ids;
	for (int i = 0; i < recipes.Num(); i++){
		FEntry* gives = recipes[i]->getGives();
		ids.Add(gives->id);
	}
	return ids;
}

bool UCraftingManager::craftItem(FString id){
	Recipe* recipe = getRecipe(id);
	if (recipe != nullptr){
		if (canCraft(id)){
			TArray<FEntry*> needs = recipe->getNeeds();
			for (int i = 0; i < needs.Num(); i++){
				inventory->removeFromInventory(needs[i]->id, needs[i]->amount);
			}
			FEntry* gives = recipe->getGives();
			inventory->addToInventory(gives->id, gives->amount);
			return true;
		}
	}
	return false;
}

Recipe* UCraftingManager::getRecipe(FString id){
	for (int i = 0; i < recipes.Num(); i++){
		if (id.Equals(recipes[i]->getGives()->id)){
			return recipes[i];
		}
	}
	return nullptr;
}
