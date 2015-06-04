// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "ItemManager.h"
#include "ItemConverter.h"
#include "../../DynamicData/DDReg.h"

UItemManager* UItemManager::getInstance() {
	static UItemManager* instance = NewObject<UItemManager>();
	return instance;
}

UItemManager::UItemManager(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer){
	AddToRoot();
	items.Init(0);
	loadItems();
}

UItemManager::~UItemManager(){}

void UItemManager::loadItems(){
	ItemConverter* ic = ItemConverter::getInstance();
	TArray<DDObject*> itemsRaw = DDReg::load(FPaths::GameDir() + "items.json");

	for (int i = 0; i < itemsRaw.Num(); i++) {
		Item* item = static_cast<Item*>(itemsRaw[i]);

		items.Add(item);
	}
}

UBlueprintItem* UItemManager::getItem(FString id){
	UBlueprintItem* result = NewObject<UBlueprintItem>();
	for (int i = 0; i < items.Num(); i++){
		if (id.Equals(items[i]->getID())){
			result = items[i]->getBlueprint();
		}
	}
	return result;
}

TArray<Item*> UItemManager::getItems(){
	return items;
}