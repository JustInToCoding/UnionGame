// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DDConverter.h"
#include "DDObject.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

/**
 * 
 */
class UNIONGAME_API DDReg
{
public:
    static void reg(DDConverter* converter);

	static TArray<DDObject*> load(FString path);

	static void save(FString path, TArray<DDObject*> values, DDConverter* converter);

	static void save(FString path, TArray<DDObject*> values, FString converter);

private:
	static TMap <FString, DDConverter*> _converters;
};
