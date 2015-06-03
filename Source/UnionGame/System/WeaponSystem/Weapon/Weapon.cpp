// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Weapon.h"
#include "BlueprintWeapon.h"


Weapon::Weapon() {
	_wrapper = NewObject<UBlueprintWeapon>();
	_wrapper->setWeapon(this);
	_wrapper->AddToRoot();
}
Weapon::~Weapon() {
	_wrapper->setWeapon(NULL);
	_wrapper->RemoveFromRoot();
}

//-----------------------------------------------------------------------------------
//  Setter
//-----------------------------------------------------------------------------------

void Weapon::setID(FString id) {
	_id = id;
}
void Weapon::setDamage(float damage) {
	_damage = damage;
}
