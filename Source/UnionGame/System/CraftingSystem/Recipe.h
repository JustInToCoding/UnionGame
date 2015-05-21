#pragma once

#include "DynamicData/DDObject.h"
#include "System/InventorySystem/Inventory.h"

class UNIONGAME_API Recipe : public DDObject
{
	friend class RecipeConverter;
public:
	Recipe(FString id, TArray<FEntry*> needs, FEntry* gives);
	~Recipe();

	FString getID();
	TArray<FEntry*> getNeeds();
	FEntry* getGives();
	FString toString();

private:
	FString _id;
	TArray<FEntry*> _needs;
	FEntry* _gives;
};