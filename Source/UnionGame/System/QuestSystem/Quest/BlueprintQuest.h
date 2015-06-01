// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BlueprintQuest.generated.h"

class Quest;
class UBlueprintQuestTask;

UENUM(BlueprintType)
enum EQuestStateEnum
{
	VE_NotSet			UMETA(DisplayName = "State not set"),
	VE_NotStartable     UMETA(DisplayName = "Not Startable"),
	VE_Startable		UMETA(DisplayName = "Startable"),
	VE_Running		    UMETA(DisplayName = "Running"),
	VE_Completed	    UMETA(DisplayName = "Completed"),
	VE_ClosedSuccessful UMETA(DisplayName = "Closed Successful"),
	VE_Failed	        UMETA(DisplayName = "Failed"),
	VE_ClosedFailed	    UMETA(DisplayName = "Closed Failed")
};

/**
 * 
 */
UCLASS()
class UNIONGAME_API UBlueprintQuest : public UObject
{
	GENERATED_BODY()

	friend class Quest;

private:
	Quest* _adapter;
	UWorld* _world;


	void setQuest(Quest* adapter);

public:
	Quest* getQuest() { return _adapter; }

	void setWorld(UWorld* world);

	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		void activate();
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		void trigger();
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		void updateTask(FString id, int32 amount);
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		TArray<FString> getMessages();
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		EQuestStateEnum getCurrentState();
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		UBlueprintQuestTask* getTask();
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		UBlueprintQuestTask* getFailstate();

	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
		void addEventID(FString eventID);

	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		FString getID();
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		TArray<FString> getEventIDs();
	UFUNCTION(BlueprintPure, Category = "QuestSystem")
		bool isRedoable();
};
