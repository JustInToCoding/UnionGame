// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.h"
#include "BlueprintItem.generated.h"

UCLASS()
class UNIONGAME_API UBlueprintItem : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = Items)
		FString getID();
	UFUNCTION(BlueprintPure, Category = Items)
		FString getName();
	UFUNCTION(BlueprintPure, Category = Items)
		FString getDesc();
	UFUNCTION(BlueprintPure, Category = Items)
		FString getSprite();
	
private:
	Item* item;
	friend class Item;	
	
};
