// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "QuestEvent.h"
#include "QuestTrigger.generated.h"

class UQuest;

/**
 * 
 */
UCLASS()
class UNIONGAME_API UQuestTrigger : public UObject
{
	GENERATED_BODY()

private:
	AQuestEvent* _event;

public:
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
	void activate();

	void init(AQuestEvent* event);
	
	
};
