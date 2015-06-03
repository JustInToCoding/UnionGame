// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Weapon.h"
#include "BlueprintWeapon.h"

void UBlueprintWeapon::setWeapon(Weapon* adapter) {
	_adapter = adapter;
}

FString UBlueprintWeapon::getID() {
	if (_adapter != NULL) {
		return _adapter->getID();
	}
	return "";
}
float UBlueprintWeapon::getDamage() {
	if (_adapter != NULL) {
		return _adapter->getDamage();
	}
	return 0.0f;
}
