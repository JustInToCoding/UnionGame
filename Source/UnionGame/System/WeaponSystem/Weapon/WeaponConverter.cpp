// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "WeaponConverter.h"
#include "Weapon.h"
#include "../../../DynamicData/DDReg.h"

WeaponConverter* WeaponConverter::getInstance() {
	static WeaponConverter instance;
	static bool isInReg = false;

	if (!isInReg) {
		DDReg::reg(&instance);
	}

	return &instance;
}
WeaponConverter::WeaponConverter() : DDConverter("WeaponConverter") {
}

WeaponConverter::~WeaponConverter() {
}

DDObject* WeaponConverter::getDDObject(TSharedPtr<FJsonObject> value) {
	Weapon* weapon = new Weapon();

	weapon->setID(value->GetStringField("id"));
	weapon->setDamage(value->GetNumberField("damage"));

	return weapon;
}

TSharedPtr<FJsonObject> WeaponConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	Weapon* weapon = static_cast<Weapon*>(value);

	result->SetStringField("id", weapon->getID());
	result->SetNumberField("damage", weapon->getDamage());

	return result;
}
