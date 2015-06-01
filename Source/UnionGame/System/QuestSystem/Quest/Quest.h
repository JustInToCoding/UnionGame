// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "QuestTask.h"
#include "BlueprintQuest.h"
#include "../../../DynamicData/DDObject.h"

class QuestState;

/**
 * 
 */
class UNIONGAME_API Quest : public DDObject
{
	friend TSubclassOf<QuestState>;

private:
	FString _id;
	TArray<FString> _eventIDs;
	bool _redoable;
	QuestTask* _task;
	QuestTask* _failstate;
	TArray<FString> _startingMessages;
	TArray<FString> _runningMessages;
	TArray<FString> _completedMessages;
	TArray<FString> _closedSuccessfulMessages;
	TArray<FString> _closedFailedMessages;

	QuestState* _currentState;
	UBlueprintQuest* _wrapper;

public:
	Quest();
	~Quest();

	UBlueprintQuest* getBlueprint() { return _wrapper; }

	void activate();
	void trigger();
	void updateTask(FString id, int amount);
	void testState();
	TArray<FString> getMessages();

//-----------------------------------------------------------------------------------
//  Setter
//-----------------------------------------------------------------------------------
	void setID(FString id);
	void addEventID(FString eventID);
	void removeEventID();
	void setRedoable(bool redoaboe);
	void setTask(QuestTask* taskID);
	void setFailstate(QuestTask* failID);
	void setStartingMsg(TArray<FString> msg);
	void setRunningMsg(TArray<FString> msg);
	void setCompletedMsg(TArray<FString> msg);
	void setClosedSuccessfulMsg(TArray<FString> msg);
	void setClosedFailedMsg(TArray<FString> msg);
	void setCurrentState(QuestState* newState);

//-----------------------------------------------------------------------------------
//  Getter
//-----------------------------------------------------------------------------------
	FString getID() { return _id; }
	TArray<FString> getEventIDs() { return _eventIDs; }
	bool isRedoable() { return _redoable; }
	EQuestStateEnum getCurrentState();
	QuestTask* getTask() { return _task; }
	QuestTask* getFailstate() { return _failstate; }
	TArray<FString> getStartingMessages() { return _startingMessages; }
	TArray<FString> getRunningMessages() { return _runningMessages; }
	TArray<FString> getCompletedMessages() { return _completedMessages; }
	TArray<FString> getClosedSuccessfulMessages() { return _closedSuccessfulMessages; }
	TArray<FString> getClosedFailedMessages() { return _closedFailedMessages; }
};
