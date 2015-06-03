// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BlueprintDino.h"
#include "../../../DynamicData/DDObject.h"

/**
 * 
 */
class UNIONGAME_API DinoInformation : public DDObject
{
private:
	FString _id;
	float _life;

	UBlueprintDino* _wrapper;

public:
	DinoInformation();
	~DinoInformation();

	UBlueprintDino* getBlueprint() { return _wrapper; }

	//-----------------------------------------------------------------------------------
	//  Setter
	//-----------------------------------------------------------------------------------
	void setID(FString id);
	void setLife(float life);

	//-----------------------------------------------------------------------------------
	//  Getter
	//-----------------------------------------------------------------------------------
	FString getID() { return _id; }
	float getLife() { return _life; }
};
