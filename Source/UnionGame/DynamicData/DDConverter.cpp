// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "DDConverter.h"

DDConverter::DDConverter() {
}

DDConverter::DDConverter(FString name) {
	_name = name;
}

DDConverter::~DDConverter() {
}

TArray<DDObject*> DDConverter::JSONToDDO(rapidjson::Value& values) {
	TArray<DDObject*> result;

	if (values.IsArray()) {
		for (rapidjson::SizeType i = 0; i < values.Size(); i++) {
			result.Add(getDDObject(values[i]));
		}
	}

	return result;
}
rapidjson::Value* DDConverter::DDOToJSON(TArray<DDObject*> ddos, rapidjson::Document::AllocatorType& allocator) {
	rapidjson::Value* result;
	rapidjson::Value* arrayEntry;

	result = new rapidjson::Value(rapidjson::kArrayType);

	for (int i = 0; i != ddos.Num(); i++) {
		arrayEntry = getJSON(ddos[i], allocator);
		result->PushBack(*arrayEntry, allocator);
	}

	return result;
}
FString DDConverter::getName() {
	return _name;
}

DDObject* DDConverter::getDDObject(rapidjson::Value& value) {
	return new DDObject();
}
rapidjson::Value* DDConverter::getJSON(DDObject* value, rapidjson::Document::AllocatorType& allocator) {
	return new rapidjson::Value(rapidjson::kObjectType);
}