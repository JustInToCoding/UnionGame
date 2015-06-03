// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BlueprintDino.generated.h"

class DinoInformation;

/**
 * 
 */
UCLASS()
class UNIONGAME_API UBlueprintDino : public UObject
{
	GENERATED_BODY()
	
	friend class DinoInformation;

private:
	DinoInformation* _adapter;

	void setDino(DinoInformation* adapter);

public:
	DinoInformation* getWeapon() { return _adapter; }

	UFUNCTION(BlueprintPure, Category = "DinoSystem")
		FString getID();
	UFUNCTION(BlueprintPure, Category = "DinoSystem")
		float getLife();
};
