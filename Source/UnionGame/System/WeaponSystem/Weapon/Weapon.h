// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BlueprintWeapon.h"
#include "../../../DynamicData/DDObject.h"

/**
*
*/
class UNIONGAME_API Weapon : public DDObject
{
private:
	FString _id;
	float _damage;

	UBlueprintWeapon* _wrapper;

public:
	Weapon();
	~Weapon();

	UBlueprintWeapon* getBlueprint() { return _wrapper; }

	//-----------------------------------------------------------------------------------
	//  Setter
	//-----------------------------------------------------------------------------------
	void setID(FString id);
	void setDamage(float damage);

	//-----------------------------------------------------------------------------------
	//  Getter
	//-----------------------------------------------------------------------------------
	FString getID() { return _id; }
	float getDamage() { return _damage; }
};
