// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Json.h"
#include "DDReg.h"

void DDReg::reg(DDConverter* converter) {
	_converters.Add(converter->getName(), converter);
}

TArray<DDObject*> DDReg::load(FString path) {
	TArray<DDObject*> Result;
	FString JsonStr;
	FString fullPath = FPaths::GameDir() + "jsonFiles/" + path + ".json";

	FFileHelper::LoadFileToString(JsonStr, *fullPath);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = FJsonStringReader::Create(JsonStr);
	TSharedPtr<FJsonObject> JsonRoot = MakeShareable(new FJsonObject());
	bool serialized = FJsonSerializer::Deserialize(JsonReader, JsonRoot);

	if (serialized){
		// read tile data from json
		FString ConverterName = JsonRoot->GetStringField("DDConverter");
		TSharedPtr<FJsonValue> Values = JsonRoot->TryGetField("Values");

		DDConverter* Converter;
		Converter = _converters[ConverterName];

		if (&Converter != NULL) {
			Result = Converter->JSONToDDO(Values);
		}
	}

	return Result;
}

void DDReg::save(FString path, TArray<DDObject*> values, FString converterName) {
	DDConverter* converter;
	converter = _converters[converterName];
	save(path, values, converter);
}

void DDReg::save(FString path, TArray<DDObject*> values, DDConverter* converter) {
	TSharedRef<FJsonObject> JsonRoot = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonValue> JsonValues;
	FString fullPath = FPaths::GameDir() + "jsonFiles/" + path + ".json";

	JsonRoot->SetStringField("DDConverter", converter->getName());

	JsonValues = converter->DDOToJSON(values);

	JsonRoot->SetField("Values", JsonValues);

	FString JsonStr;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	FJsonSerializer::Serialize(JsonRoot, JsonWriter);

	FFileHelper::SaveStringToFile(JsonStr, *fullPath);
}

TMap<FString, DDConverter*> DDReg::_converters;