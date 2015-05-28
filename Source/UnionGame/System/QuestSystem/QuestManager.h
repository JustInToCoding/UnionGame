// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestManager.generated.h"

class UBlueprintQuest;
class UQuestEvent;

/**
 * 
 */
UCLASS()
class UNIONGAME_API UQuestManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//Event
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static void registerEvent(TSubclassOf<UQuestEvent> questEventClass, FString id);
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		static UQuestEvent* getEvent(FString id);

	//Quest
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static void loadQuests(FString file);
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		static UBlueprintQuest* getQuest(FString id);

	//Updating
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static void activate(FString questID);
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		static void update(FString id);

private:
	static TMap<FString, UBlueprintQuest*> _questsMap;
	static TMap<FString, UQuestEvent*> _eventsMap;
	
	
};