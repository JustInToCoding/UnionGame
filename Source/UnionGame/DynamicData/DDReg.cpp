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
	FFileHelper::LoadFileToString(JsonStr, *path);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = FJsonStringReader::Create(JsonStr);
	TSharedPtr<FJsonObject> JsonRoot = MakeShareable(new FJsonObject());
	bool serialized = FJsonSerializer::Deserialize(JsonReader, JsonRoot);

	if (serialized){
		// read tile data from json
		FString ConverterName = JsonRoot->GetStringField(TEXT("DDConverter"));
		TSharedPtr<FJsonValue> Values = JsonRoot->TryGetField(TEXT("Values"));

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



	//rapidjson::Value* JSONValues;
	//rapidjson::Document root;
	//root.SetObject();
	//rapidjson::Document::AllocatorType& allocator = root.GetAllocator();

	////Get Converter's name
	//rapidjson::Value DDConverterName(rapidjson::kStringType);
	//DDConverterName.SetString(TCHAR_TO_ANSI(*converter->getName()), allocator);
	//root.AddMember("DDConverter", DDConverterName, allocator);

	////Get Values
	//JSONValues = (converter->DDOToJSON(values, allocator));

	////Write Object to String
	//rapidjson::StringBuffer result;
	//rapidjson::Writer<rapidjson::StringBuffer> writer(result);

	//root.AddMember("values", *JSONValues, allocator);
	//root.Accept(writer);

	//FString json = result.GetString();

	////Write out String to File
	//FFileHelper::SaveStringToFile(json, *path);

	//delete JSONValues;
}

TMap<FString, DDConverter*> DDReg::_converters;