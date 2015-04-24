// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DDObject.h"
#include "Json.h"
#include "rapidjson/document.h"

/**
 * 
 */
class UNIONGAME_API DDConverter
{
public:
	~DDConverter();

	virtual TArray<DDObject*> JSONToDDO(TSharedPtr<FJsonValue> values);
	virtual TSharedPtr<FJsonValue> DDOToJSON(TArray<DDObject*> ddos);
	FString getName();

protected:
	FString _name;

	DDConverter(FString name);

	virtual DDObject* getDDObject(TSharedPtr<FJsonObject> value);
	virtual TSharedPtr<FJsonObject> getJSON(DDObject* value);
private:
	DDConverter();
};
