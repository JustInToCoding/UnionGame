// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BlueprintWeapon.generated.h"

class Weapon;

/**
*
*/
UCLASS()
class UNIONGAME_API UBlueprintWeapon : public UObject
{
	GENERATED_BODY()

	friend class Weapon;

private:
	Weapon* _adapter;

	void setWeapon(Weapon* adapter);

public:
	Weapon* getWeapon() { return _adapter; }

	UFUNCTION(BlueprintPure, Category = "WeaponSystem")
		FString getID();
	UFUNCTION(BlueprintPure, Category = "WeaponSystem")
		float getDamage();
};
