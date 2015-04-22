// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Core.h>
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

	template<typename T>
	static TArray<T*> load(FString path);
	static TArray<DDObject*> load(FString path);

	template<typename T>
	static void save(FString path, TArray<T*> values, DDConverter* converter);
	static void save(FString path, TArray<DDObject*> values, DDConverter* converter);

	template<typename T>
	static void save(FString path, TArray<T*> values, FString converter);
	static void save(FString path, TArray<DDObject*> values, FString converter);

private:
	static TMap <FString, DDConverter*> _converters;
};
