// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaponManager.generated.h"

class UBlueprintWeapon;

/**
*
*/
UCLASS()
class UNIONGAME_API UWeaponManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Quest
	UFUNCTION(BlueprintCallable, Category = "WeaponSystem")
		static void loadWeapons();
	UFUNCTION(BlueprintPure, Category = "WeaponSystem")
		static UBlueprintWeapon* getWeapon(FString id);

private:
	static TMap<FString, UBlueprintWeapon*> _weaponsMap;
};
