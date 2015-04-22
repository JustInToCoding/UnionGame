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

TArray<DDObject*> DDConverter::JSONToDDO(Value& values) {
	TArray<DDObject*> result;

	if (values.IsArray()) {
		for (SizeType i = 0; i < values.Size(); i++) {
			result.Add(getDDObject(values[i]));
		}
	}

	return result;
}
Value* DDConverter::DDOToJSON(TArray<DDObject*> ddos, Document::AllocatorType& allocator) {
	Value* result;
	Value* arrayEntry;

	result = new Value(kArrayType);

	for (int i = 0; i != ddos.Num(); i++) {
		arrayEntry = getJSON(ddos[i], allocator);
		result->PushBack(*arrayEntry, allocator);
	}

	return result;
}
FString DDConverter::getName() {
	return _name;
}

DDObject* DDConverter::getDDObject(Value& value) {
	return new DDObject();
}
Value* DDConverter::getJSON(DDObject* value, Document::AllocatorType& allocator) {
	return new Value(kObjectType);
}