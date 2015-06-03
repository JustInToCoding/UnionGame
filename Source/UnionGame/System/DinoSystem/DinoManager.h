// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DinoManager.generated.h"

class UBlueprintDino;

/**
*
*/
UCLASS()
class UNIONGAME_API UDinoManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Quest
	UFUNCTION(BlueprintCallable, Category = "DinoSystem")
		static void loadDinos();
	UFUNCTION(BlueprintPure, Category = "DinoSystem")
		static UBlueprintDino* getDino(FString id);

private:
	static TMap<FString, UBlueprintDino*> _dinosMap;
};
