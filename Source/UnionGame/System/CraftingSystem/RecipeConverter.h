#pragma once

#include "DynamicData/DDConverter.h"
#include "DynamicData/DDObject.h"
#include "System/InventorySystem/Inventory.h"

class UNIONGAME_API RecipeConverter : public DDConverter
{
public:
	static RecipeConverter* getInstance();
	~RecipeConverter();

protected:
	DDObject* getDDObject(TSharedPtr<FJsonObject> value);
	TSharedPtr<FJsonObject> getJSON(DDObject* value);

private:
	RecipeConverter();
	TArray<FEntry*> GetSubelements(TArray<TSharedPtr<FJsonValue>> sourceArray);
	FEntry* GetSubelement(TSharedPtr<FJsonValue> source);
	TArray<TSharedPtr<FJsonValue>> ConstructSubelements(TArray<FEntry*> values);
	TSharedPtr<FJsonValue> ConstructSubelement(FEntry* value);
};
