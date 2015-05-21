#include "UnionGame.h"
#include "RecipeConverter.h"
#include "Recipe.h"
#include "DynamicData/DDReg.h"


RecipeConverter* RecipeConverter::getInstance() {
	static RecipeConverter instance;
	static bool isInReg = false;

	if (!isInReg) {
		DDReg::reg(&instance);
	}

	return &instance;
}

RecipeConverter::RecipeConverter() : DDConverter("RecipeConverter") {
}

RecipeConverter::~RecipeConverter() {
}

DDObject* RecipeConverter::getDDObject(TSharedPtr<FJsonObject> value) {
	FString id;
	TArray<FEntry*> needs, gives;

	id = value->GetStringField(TEXT("id"));
	needs = GetSubelements(value->GetArrayField(TEXT("needs")));
	gives = GetSubelements(value->GetArrayField(TEXT("gives")));

	return new Recipe(id, needs, gives);
}

TArray<FEntry*> RecipeConverter::GetSubelements(TArray<TSharedPtr<FJsonValue>> sourceArray) {
	TArray<FEntry*> result;

	for (int i = 0; i < sourceArray.Num(); i++){
		result.Add(GetSubelement(sourceArray[i]));
	}

	return result;
}

FEntry* RecipeConverter::GetSubelement(TSharedPtr<FJsonValue> source){
	TSharedPtr<FJsonObject> object = source->AsObject();
	FEntry* result = new FEntry();

	result->id = object->GetStringField(TEXT("id"));
	result->amount = object->GetNumberField(TEXT("amount"));

	return result;
}

TSharedPtr<FJsonObject> RecipeConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	Recipe* recipe = static_cast<Recipe*>(value);

	result->SetStringField(TEXT("id"), recipe->getID());
	result->SetArrayField(TEXT("needs"), ConstructSubelements(recipe->getNeeds()));
	result->SetArrayField(TEXT("gives"), ConstructSubelements(recipe->getGives()));

	return result;
}

TArray<TSharedPtr<FJsonValue>> RecipeConverter::ConstructSubelements(TArray<FEntry*> values){
	TArray<TSharedPtr<FJsonValue>> result;

	for (int i = 0; i < values.Num(); i++){
		result.Add(ConstructSubelement(values[i]));
	}

	return result;
}

TSharedPtr<FJsonValue> RecipeConverter::ConstructSubelement(FEntry* value){
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	result->SetStringField(TEXT("id"), value->id);
	result->SetNumberField(TEXT("amount"), value->amount);

	return MakeShareable(new FJsonValueObject(result));
}
