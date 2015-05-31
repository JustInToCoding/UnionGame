// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BlueprintQuestTask.generated.h"

class QuestTask;

/**
 * 
 */
UCLASS()
class UNIONGAME_API UBlueprintQuestTask : public UObject
{
	GENERATED_BODY()

	friend class QuestTask;
	friend class QuestTask_Timer;

private:
	QuestTask* _adapter;

	void timerStart(int time);
	void timerRunOut();

public:
	QuestTask* getTask();

	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		void start();
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		void update(FString id, int32 amount);

	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		bool isComplete();
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		bool isWrapperTask();
	
};
