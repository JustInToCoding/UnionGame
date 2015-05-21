// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "DDConverter.h"
#include "JsonValue.h"

DDConverter::DDConverter() {
}

DDConverter::DDConverter(FString name) {
	_name = name;
}

DDConverter::~DDConverter() {
}

TArray<DDObject*> DDConverter::JSONToDDO(TSharedPtr<FJsonValue> values) {
	TArray<DDObject*> result;

	TArray<TSharedPtr<FJsonValue>> valuesArray = values->AsArray();

	for (int i = 0; i < valuesArray.Num(); i++) {
		result.Add(getDDObject(valuesArray[i]->AsObject()));
	}

	return result;
}
TSharedPtr<FJsonValue> DDConverter::DDOToJSON(TArray<DDObject*> ddos) {
	TArray<TSharedPtr<FJsonValue>> valuesArray;
	FJsonObject result;

	for (int i = 0; i != ddos.Num(); i++) {
		TSharedPtr<FJsonObject> object = getJSON(ddos[i]);
		TSharedPtr<FJsonValue> value = MakeShareable(new FJsonValueObject(object));
		valuesArray.Add(value);
	}

	result.SetArrayField(TEXT("temp"), valuesArray);

	return result.TryGetField("temp");
}
FString DDConverter::getName() {
	return _name;
}

DDObject* DDConverter::getDDObject(TSharedPtr<FJsonObject> value) {
	return new DDObject();
}
TSharedPtr<FJsonObject> DDConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> pointer = MakeShareable(new FJsonObject());

	return pointer;
}