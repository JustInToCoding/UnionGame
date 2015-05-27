// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DynamicData/DDConverter.h"
#include "../../DynamicData/DDObject.h"

/**
 * 
 */
class UNIONGAME_API ItemConverter : public DDConverter
{
public:
	static ItemConverter* getInstance();
	~ItemConverter();

protected:
	DDObject* getDDObject(TSharedPtr<FJsonObject> value);
	TSharedPtr<FJsonObject> getJSON(DDObject* value);

private:
	ItemConverter();
};
