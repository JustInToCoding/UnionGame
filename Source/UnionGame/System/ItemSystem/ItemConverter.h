// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DynamicData/DDConverter.h"
#include "../../DynamicData/DDObject.h"
#include "../../DynamicData/rapidjson/document.h"

/**
 * 
 */
class UNIONGAME_API ItemConverter : public DDConverter
{
public:
	static ItemConverter* getInstance();
	~ItemConverter();

protected:
	DDObject* getDDObject(rapidjson::Value& value);
	rapidjson::Value* getJSON(DDObject* value, rapidjson::Document::AllocatorType& allocator);

private:
	ItemConverter();
};
