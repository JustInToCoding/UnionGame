// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestState.h"
#include "Quest.h"
#include "QuestTask.h"
#include "BlueprintQuest.h"
#include "../QuestEvent.h"
#include "../QuestManager.h"

//---------------------------------------------------------------------------
//  Default implementation QuestState-Functions
//---------------------------------------------------------------------------
void QuestState::begin(Quest* quest) {
	//UE_LOG(LogTemp, Warning, TEXT("In this state is begin not implemented."));
}
void QuestState::activate(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("In this state is activate not implemented."));
}
void QuestState::trigger(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("In this state is trigger not implemented."));
}
void QuestState::testState(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("In this state is testState not implemented."));
}
void QuestState::updateTask(Quest* quest, FString id, int amount) {
	UE_LOG(LogTemp, Warning, TEXT("In this state is updateTask not implemented."));
}
TArray<FString> QuestState::getMessages(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("In this state is getMessages not implemented."));
	TArray<FString> result;

	return result;
}
EQuestStateEnum QuestState::getType() {
	return EQuestStateEnum::VE_NotSet;
}

//---------------------------------------------------------------------------
//  NotStartable implementation
//---------------------------------------------------------------------------
EQuestStateEnum QuestState_NotStartable::getType() {
	return EQuestStateEnum::VE_NotStartable;
}
void QuestState_NotStartable::activate(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("QuestState activated."));
	quest->setCurrentState(new QuestState_Startable());
}


//---------------------------------------------------------------------------
//  Startable implementation
//---------------------------------------------------------------------------
EQuestStateEnum QuestState_Startable::getType() {
	return EQuestStateEnum::VE_Startable;
}
void QuestState_Startable::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (FString eventID : eventIDs) {
		UQuestEvent* qEvent = UQuestManager::getEvent(eventID);
		if (qEvent != NULL) {
			qEvent->startableEvent(quest->getBlueprint());
		}
	}
	//TODO: quest->reset();
}
TArray<FString> QuestState_Startable::getMessages(Quest* quest) {
	return quest->getStartingMessages();
}
void QuestState_Startable::trigger(Quest* quest) {
	quest->setCurrentState(new QuestState_Running());
}


//---------------------------------------------------------------------------
//  Running implementation
//---------------------------------------------------------------------------
EQuestStateEnum QuestState_Running::getType() {
	return EQuestStateEnum::VE_Running;
}
void QuestState_Running::begin(Quest* quest) {
	UE_LOG(LogQuestSystem, Log, TEXT("Quest (ID: %s) now running"), *quest->getID());
	TArray<FString> eventIDs = quest->getEventIDs();

	for (FString eventID : eventIDs) {
		UQuestEvent* qEvent = UQuestManager::getEvent(eventID);
		if (qEvent != NULL) {
			qEvent->startedEvent(quest->getBlueprint());
		}
	}

	QuestTask* task = quest->getTask();
	QuestTask* fail = quest->getFailstate();

	if (task != NULL) {
		task->start();
	}
	if (fail != NULL) {
		fail->start();
	}

	testState(quest);
}
TArray<FString> QuestState_Running::getMessages(Quest* quest) {
	return quest->getRunningMessages();
}
void QuestState_Running::testState(Quest* quest) {
	bool isFinished = true;
	bool isFailed = false;

	QuestTask* task = quest->getTask();

	if (task != NULL) {
		isFinished = task->isComplete();
	}
	
	QuestTask* failstate = quest->getFailstate();

	if (failstate != NULL) {
		isFailed = failstate->isComplete();
	}

	if (isFinished || isFailed) {
		task->end();
		failstate->end();
		
		if (isFinished) {
			quest->setCurrentState(new QuestState_Completed());
		}
		else if (isFailed) {
			quest->setCurrentState(new QuestState_Failed());
		}
	}
}
void QuestState_Running::updateTask(Quest* quest, FString id, int amount) {
	QuestTask* task = quest->getTask();

	if (task != NULL) {
		task->update(id, amount);
	}

	QuestTask* failstate = quest->getFailstate();

	if (failstate != NULL) {
		failstate->update(id, amount);
	}

	testState(quest);
}


//---------------------------------------------------------------------------
//  Completed implementation
//---------------------------------------------------------------------------
EQuestStateEnum QuestState_Completed::getType() {
	return EQuestStateEnum::VE_Completed;
}
void QuestState_Completed::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (FString eventID : eventIDs) {
		UQuestEvent* qEvent = UQuestManager::getEvent(eventID);
		if (qEvent != NULL) {
			qEvent->completedEvent(quest->getBlueprint());
		}
	}
}
TArray<FString> QuestState_Completed::getMessages(Quest* quest) {
	return quest->getCompletedMessages();
}
void QuestState_Completed::trigger(Quest* quest) {
	quest->setCurrentState(new QuestState_ClosedSuccessful());
}


//---------------------------------------------------------------------------
//  Closed (Successful) implementation
//---------------------------------------------------------------------------
EQuestStateEnum QuestState_ClosedSuccessful::getType() {
	return EQuestStateEnum::VE_ClosedSuccessful;
}
void QuestState_ClosedSuccessful::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (FString eventID : eventIDs) {
		UQuestEvent* qEvent = UQuestManager::getEvent(eventID);
		if (qEvent != NULL) {
			qEvent->successfulClosedEvent(quest->getBlueprint());
		}
	}
}
TArray<FString> QuestState_ClosedSuccessful::getMessages(Quest* quest) {
	return quest->getClosedSuccessfulMessages();
}


//---------------------------------------------------------------------------
//  Failed implementation
//---------------------------------------------------------------------------
EQuestStateEnum QuestState_Failed::getType() {
	return EQuestStateEnum::VE_Failed;
}
void QuestState_Failed::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (FString eventID : eventIDs) {
		UQuestEvent* qEvent = UQuestManager::getEvent(eventID);
		if (qEvent != NULL) {
			qEvent->failedEvent(quest->getBlueprint());
		}
	}
	testState(quest);
}
void QuestState_Failed::testState(Quest* quest) {
	if (quest->isRedoable()) {
		quest->setCurrentState(new QuestState_Startable());
	}
	else {
		quest->setCurrentState(new QuestState_ClosedFailed());
	}
}


//---------------------------------------------------------------------------
//  Closed (Failed) implementation
//---------------------------------------------------------------------------
EQuestStateEnum QuestState_ClosedFailed::getType() {
	return EQuestStateEnum::VE_ClosedFailed;
}
void QuestState_ClosedFailed::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (FString eventID : eventIDs) {
		UQuestEvent* qEvent = UQuestManager::getEvent(eventID);
		if (qEvent != NULL) {
			qEvent->failedClosedEvent(quest->getBlueprint());
		}
	}
}
TArray<FString> QuestState_ClosedFailed::getMessages(Quest* quest) {
	return quest->getClosedFailedMessages();
}