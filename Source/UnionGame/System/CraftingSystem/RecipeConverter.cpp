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
	FEntry* gives;
	TArray<FEntry*> needs;

	id = value->GetStringField(TEXT("id"));
	needs = GetSubelements(value->GetArrayField(TEXT("needs")));
	gives = GetSubelement(value->GetObjectField(TEXT("gives")));

	return new Recipe(id, needs, gives);
}

TArray<FEntry*> RecipeConverter::GetSubelements(TArray<TSharedPtr<FJsonValue>> sourceArray) {
	TArray<FEntry*> result;

	for (int i = 0; i < sourceArray.Num(); i++){
		result.Add(GetSubelement(sourceArray[i]->AsObject()));
	}

	return result;
}

FEntry* RecipeConverter::GetSubelement(TSharedPtr<FJsonObject> source){
	FEntry* result = new FEntry();

	result->id = source->GetStringField(TEXT("id"));
	result->amount = source->GetNumberField(TEXT("amount"));

	return result;
}

TSharedPtr<FJsonObject> RecipeConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	Recipe* recipe = static_cast<Recipe*>(value);

	result->SetStringField("id", recipe->getID());
	result->SetArrayField("needs", ConstructSubelements(recipe->getNeeds()));
	result->SetObjectField("gives", ConstructSubelement(recipe->getGives()));

	return result;
}

TArray<TSharedPtr<FJsonValue>> RecipeConverter::ConstructSubelements(TArray<FEntry*> values){
	TArray<TSharedPtr<FJsonValue>> result;

	for (int i = 0; i < values.Num(); i++){
		TSharedPtr<FJsonObject> element = ConstructSubelement(values[i]);
		result.Add(MakeShareable(new FJsonValueObject(element)));
	}

	return result;
}

TSharedPtr<FJsonObject> RecipeConverter::ConstructSubelement(FEntry* value){
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	result->SetStringField("id", value->id);
	result->SetNumberField("amount", value->amount);

	return result;
}
