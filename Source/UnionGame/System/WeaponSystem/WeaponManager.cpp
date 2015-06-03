// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "WeaponManager.h"
#include "../../DynamicData/DDReg.h"
#include "Weapon/WeaponConverter.h"
#include "Weapon/BlueprintWeapon.h"
#include "Weapon/Weapon.h"

//Quest
void UWeaponManager::loadWeapons() {
	UE_LOG(LogWeaponSystem, Log, TEXT("start loading weapons"));
	WeaponConverter* converter = WeaponConverter::getInstance();
	
	TArray<DDObject*> loaded = DDReg::load("weapons");

	if (loaded.Num() <= 0) {
		UE_LOG(LogWeaponSystem, Error, TEXT("No Weapons have been loaded."));
		UE_LOG(LogWeaponSystem, Error, TEXT("  This might be because of errors in the JSON-File."));
		UE_LOG(LogWeaponSystem, Error, TEXT("  Check if there are missplaced commas, brackets or tags."));
	}

	for (DDObject* ddo : loaded) {
		Weapon* weapon = static_cast<Weapon*>(ddo);
		UE_LOG(LogWeaponSystem, Log, TEXT("  weapon %s"), *weapon->getID());

		if (weapon != NULL) {
			_weaponsMap.Add(weapon->getID(), weapon->getBlueprint());
		}
	}
	UE_LOG(LogWeaponSystem, Log, TEXT("end loading weapons"));
}
UBlueprintWeapon* UWeaponManager::getWeapon(FString id) {
	UBlueprintWeapon* weapon = NULL;

	if (_weaponsMap.Contains(id)) {
		weapon = _weaponsMap[id];
	}

	if (weapon == NULL) {
		weapon = NewObject<UBlueprintWeapon>();
	}

	return weapon;
}

TMap<FString, UBlueprintWeapon*> UWeaponManager::_weaponsMap;
