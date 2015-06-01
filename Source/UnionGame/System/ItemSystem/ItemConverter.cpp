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

	id = value->GetStringField(TEXT("id"));
	name = value->GetStringField(TEXT("name"));
	desc = value->GetStringField(TEXT("desc"));
	sprite = value->GetStringField(TEXT("sprite"));

	return new Item(id, name, desc, sprite);
}

TSharedPtr<FJsonObject> ItemConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	Item* item = static_cast<Item*>(value);
	
	result->SetStringField(TEXT("id"), item->getID());
	result->SetStringField(TEXT("name"), item->getName());
	result->SetStringField(TEXT("desc"), item->getDesc());
	result->SetStringField(TEXT("sprite"), item->getSprite());

	return result;
}
