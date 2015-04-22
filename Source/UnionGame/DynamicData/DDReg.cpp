// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "DDReg.h"

void DDReg::reg(DDConverter* converter) {
	_converters.Add(converter->getName(), converter);
}

template<typename T>
TArray<T*> DDReg::load(FString path) {
	TList<DDObject*> loaded;
	TList<T*> result;

	loaded = DDReg::load(path);

	for each (DDObject* var in loaded) {
		result.push_back(dynamic_cast<T*>(var));
	}

	return result;
}
TArray<DDObject*> DDReg::load(FString path) {
	FString json, converterName;
	DDConverter* converter;
	FFileHelper::LoadFileToString(json, *path);
	TArray<DDObject*> result;
	Document root;

	root.Parse<0>(TCHAR_TO_ANSI(*json));

	if (root.IsObject() && root.HasMember("DDConverter")) {
		converterName = root["DDConverter"].GetString();
		converter = _converters[converterName];

		if (&converter != NULL){
			result = converter->JSONToDDO(root["values"]);
		}
	}
	return result;
}

template<typename T>
void DDReg::save(FString path, TArray<T*> values, FString converterName) {
	DDConverter* converter;
	converter = _converters[converterName];

	save(path, values, converter);
}
void DDReg::save(FString path, TArray<DDObject*> values, FString converterName) {
	DDConverter* converter;
	converter = _converters[converterName];

	save(path, values, converter);
}

template<typename T>
void DDReg::save(FString path, TArray<T*> values, DDConverter* converter) {
	save(path, values, converter);
}
void DDReg::save(FString path, TArray<DDObject*> values, DDConverter* converter) {
	Value* JSONValues;
	Document root;
	root.SetObject();
	Document::AllocatorType& allocator = root.GetAllocator();

	//Get Converter's name
	Value DDConverterName(kStringType);
	DDConverterName.SetString(TCHAR_TO_ANSI(*converter->getName()), allocator);
	root.AddMember("DDConverter", DDConverterName, allocator);

	//Get Values
	JSONValues = (converter->DDOToJSON(values, allocator));

	//Write Object to String
	StringBuffer result;
	Writer<StringBuffer> writer(result);

	root.AddMember("values", *JSONValues, allocator);
	root.Accept(writer);

	FString json = result.GetString();

	//Write out String to File
	FFileHelper::SaveStringToFile(json, *path);

	delete JSONValues;
}

TMap<FString, DDConverter*> DDReg::_converters;