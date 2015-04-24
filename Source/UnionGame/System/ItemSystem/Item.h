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
	Item(int id, FString name, FString desc);
	~Item();

	int getID();
	FString getName();
	FString getDesc();

private:
	Item();
	int _id;
	FString _name;
	FString _desc;
};
