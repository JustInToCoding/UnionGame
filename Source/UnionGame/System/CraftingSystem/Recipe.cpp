#include "UnionGame.h"
#include "Recipe.h"

Recipe::Recipe(FString id, TArray<FEntry*> needs, TArray<FEntry*> gives) {
	_id = id;
	_needs = needs;
	_gives = gives;
	addToMap(id);
}

Recipe::~Recipe() {
}

FString Recipe::getID() {
	return _id;
}
TArray<FEntry*> Recipe::getNeeds() {
	return _needs;
}
TArray<FEntry*> Recipe::getGives() {
	return _gives;
}
FString Recipe::toString(){
	FString string = "";
	string.Append("ID: ").Append(_id).Append("\r\n");
	string.Append("Needs: \r\n");
	for (int i = 0; i < _needs.Num(); i++){
		string.Append("\tID: ").Append(_needs[i]->id);
		string.Append("\tAmount: ").Append(FString::FromInt(_needs[i]->amount)).Append("\r\n");
	}
	string.Append("Gives: \r\n");
	for (int i = 0; i < _gives.Num(); i++){
		string.Append("\tID: ").Append(_gives[i]->id);
		string.Append("\tAmount: ").Append(FString::FromInt(_gives[i]->amount).Append("\r\n"));
	}
	return string;
}