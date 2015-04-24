// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Item.h"

Item::Item() {
}

Item::Item(int id, FString name, FString desc) {
	_id = id;
	_name = name;
	_desc = desc;
}

Item::~Item() {
}

int Item::getID() {
	return _id;
}
FString Item::getName() {
	return _name;
}
FString Item::getDesc() {
	return _desc;
}
