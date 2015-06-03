// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../DynamicData/DDConverter.h"
#include "../../../DynamicData/DDObject.h"

/**
*
*/
class UNIONGAME_API WeaponConverter : public DDConverter
{
public:
	static WeaponConverter* getInstance();
	~WeaponConverter();

protected:
	TArray<FString> getStringArray(TArray<TSharedPtr<FJsonValue>> sourceArray);
	TArray<TSharedPtr<FJsonValue>> getJSONArray(TArray<FString> sourceArray);
	DDObject* getDDObject(TSharedPtr<FJsonObject> value);
	TSharedPtr<FJsonObject> getJSON(DDObject* value);

private:
	WeaponConverter();
};
