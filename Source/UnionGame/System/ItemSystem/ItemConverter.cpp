// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "ItemConverter.h"
#include "Item.h"
#include "../../DynamicData/DDReg.h"


ItemConverter* ItemConverter::getInstance() {
	static ItemConverter instance;
	static bool isInReg = false;

	if (!isInReg) {
		DDReg::reg(&instance);
	}

	return &instance;
}

ItemConverter::ItemConverter() : DDConverter("ItemConverter") {
}

ItemConverter::~ItemConverter() {
}

DDObject* ItemConverter::getDDObject(rapidjson::Value& value) {
	int id;
	FString name, desc;

	id = value["id"].GetInt();
	name = value["name"].GetString();
	desc = value["desc"].GetString();

	return new Item(id, name, desc);
}

rapidjson::Value* ItemConverter::getJSON(DDObject* value, rapidjson::Document::AllocatorType& allocator) {
	rapidjson::Value *result, *nameJson, *descJson;
	Item* item = static_cast<Item*>(value);

	char* name = TCHAR_TO_UTF8(*item->getName());
	char* desc = TCHAR_TO_UTF8(*item->getDesc());

	result = new rapidjson::Value(rapidjson::kObjectType);
	nameJson = new rapidjson::Value(rapidjson::kStringType);
	descJson = new rapidjson::Value(rapidjson::kStringType);

	nameJson->SetString(rapidjson::StringRef(name));
	descJson->SetString(rapidjson::StringRef(desc));

	result->AddMember("id", item->getID(), allocator);
	result->AddMember("name", *nameJson, allocator);
	result->AddMember("desc", *descJson, allocator);

	return result;
}
