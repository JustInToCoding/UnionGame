// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DynamicData/DDObject.h"

/**
 * 
 */
class UNIONGAME_API Item : public DDObject
{
	friend class ItemConverter;
public:
	//Item(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
	Item(FString id, FString name, FString desc);
	~Item();

	FString getID();
	FString getName();
	FString getDesc();

private:
	FString _id;
	FString _name;
	FString _desc;
};
