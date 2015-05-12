// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "QuestEvent.generated.h"

class UQuest;
class UQuestEvent;

/**
 * 
 */
UCLASS(Blueprintable)
class UNIONGAME_API AQuestEvent : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "QuestSystem")
	virtual void OnTriggered();
	
	
	
};
