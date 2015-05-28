// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Item.h"

/*UItem::UItem(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer){
}*/

Item::Item(FString id, FString name, FString desc) {
	_id = id;
	_name = name;
	_desc = desc;
	addToMap(id);
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
