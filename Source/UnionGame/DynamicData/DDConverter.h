// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DDObject.h"
#include "rapidjson/document.h"

/**
 * 
 */
class UNIONGAME_API DDConverter
{
public:
	~DDConverter();

	virtual TArray<DDObject*> JSONToDDO(rapidjson::Value& values);
	virtual rapidjson::Value* DDOToJSON(TArray<DDObject*> ddos, rapidjson::Document::AllocatorType& allocator);
	FString getName();

protected:
	FString _name;

	DDConverter(FString name);

	virtual DDObject* getDDObject(rapidjson::Value& value);
	virtual rapidjson::Value* getJSON(DDObject* value, rapidjson::Document::AllocatorType& allocator);
private:
	DDConverter();
};
