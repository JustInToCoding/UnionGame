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

DDObject* ItemConverter::getDDObject(TSharedPtr<FJsonObject> value) {
	FString id, name, desc, sprite;

	id = value->GetStringField("id");
	name = value->GetStringField("name");
	desc = value->GetStringField("desc");
	sprite = value->GetStringField("sprite");

	return new Item(id, name, desc, sprite);
}

TSharedPtr<FJsonObject> ItemConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	Item* item = static_cast<Item*>(value);
	
	result->SetStringField("id", item->getID());
	result->SetStringField("name", item->getName());
	result->SetStringField("desc", item->getDesc());
	result->SetStringField("sprite", item->getSprite());

	return result;
}
