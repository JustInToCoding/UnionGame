// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "QuestEvent.generated.h"

class Quest;

/**
 * 
 */
UCLASS(Blueprintable)
class UNIONGAME_API UQuestEvent : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		virtual void startableEvent(UBlueprintQuest* quest);
	UFUNCTION(BlueprintImplementableEvent)
		void startedEvent(UBlueprintQuest* quest);
	UFUNCTION(BlueprintImplementableEvent)
		void completedEvent(UBlueprintQuest* quest);
	UFUNCTION(BlueprintImplementableEvent)
		void failedEvent(UBlueprintQuest* quest);
	UFUNCTION(BlueprintImplementableEvent)
		void successfulClosedEvent(UBlueprintQuest* quest);
	UFUNCTION(BlueprintImplementableEvent)
		void failedClosedEvent(UBlueprintQuest* quest);
	
};
