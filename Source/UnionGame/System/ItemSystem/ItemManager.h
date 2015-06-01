// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BlueprintItem.h"
#include "ItemManager.generated.h"

UCLASS(Blueprintable)
class UNIONGAME_API UItemManager : public UObject
{
	GENERATED_BODY()
	
	UItemManager(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
	~UItemManager();
public:
	UFUNCTION(BlueprintPure, Category = Items)
		static UItemManager* getInstance();

	UFUNCTION(BlueprintPure, Category = Items)
		UBlueprintItem* getItem(FString id);

private:
	TArray<Item*> items;
	void loadItems();
	
};
