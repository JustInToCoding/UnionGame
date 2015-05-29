// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Item.h"
#include "BlueprintItem.h"

Item::Item(FString id, FString name, FString desc, FString sprite) {
	_id = id;
	_name = name;
	_desc = desc;
	_sprite = sprite;
	BPItem = NewObject<UBlueprintItem>();
	BPItem->item = this;
	BPItem->AddToRoot();
}

Item::~Item() {
}

FString Item::getID() {
	return _id;
}
FString Item::getName() {
	return _name;
}
FString Item::getDesc() {
	return _desc;
}
FString Item::getSprite() {
	return _sprite;
}

UBlueprintItem* Item::getBlueprint(){
	return BPItem;
}
