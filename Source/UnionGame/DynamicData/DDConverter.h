// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DDObject.h"
#include "rapidjson/document.h"

using namespace rapidjson;

/**
 * 
 */
class UNIONGAME_API DDConverter
{
public:
	~DDConverter();

	virtual TArray<DDObject*> JSONToDDO(Value& values);
	virtual Value* DDOToJSON(TArray<DDObject*> ddos, Document::AllocatorType& allocator);
	FString getName();

protected:
	FString _name;

	DDConverter(FString name);

	virtual DDObject* getDDObject(Value& value);
	virtual Value* getJSON(DDObject* value, Document::AllocatorType& allocator);
private:
	DDConverter();
};
