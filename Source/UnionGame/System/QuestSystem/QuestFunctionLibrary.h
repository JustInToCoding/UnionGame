// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestFunctionLibrary.generated.h"

class UQuestTrigger;
class UQuestEvent;

/**
 * 
 */
UCLASS()
class UNIONGAME_API UQuestFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static void initQuests();
	
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static UQuestTrigger* getQuestTrigger(FString id);

	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static AQuestEvent* getQuestEvent(FString id);

	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static void setQuestEvent(FString id, AQuestEvent* qEvent);
	
protected:
	static TMap<FString, UQuestTrigger*> _triggerMap;
	static TMap<FString, AQuestEvent*> _eventMap;
};
