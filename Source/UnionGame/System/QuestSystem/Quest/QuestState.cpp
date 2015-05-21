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
void QuestState::updateTask(Quest* quest, FString id) {
	UE_LOG(LogTemp, Warning, TEXT("In this state is updateTask not implemented."));
}
TArray<FString> QuestState::getMessages(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("In this state is getMessages not implemented."));
	TArray<FString> result;

	return result;
}
EQuestTypeEnum QuestState::getType() {
	return EQuestTypeEnum::VE_NotStartable;
}

//---------------------------------------------------------------------------
//  NotStartable implementation
//---------------------------------------------------------------------------
EQuestTypeEnum QuestState_NotStartable::getType() {
	return EQuestTypeEnum::VE_NotStartable;
}
void QuestState_NotStartable::activate(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("QuestState activated."));
	quest->setCurrentState(new QuestState_Startable());
}


//---------------------------------------------------------------------------
//  Startable implementation
//---------------------------------------------------------------------------
EQuestTypeEnum QuestState_Startable::getType() {
	return EQuestTypeEnum::VE_Startable;
}
void QuestState_Startable::begin(Quest* quest) {
	UE_LOG(LogTemp, Warning, TEXT("Quest now Startable."))
	TArray<FString> eventIDs = quest->getEventIDs();

	UE_LOG(LogTemp, Warning, TEXT("Quest triggers %d events."), eventIDs.Num());
	for (FString eventID : eventIDs) {
		UE_LOG(LogTemp, Warning, TEXT("  %s"), *eventID);
		UQuestManager::getEvent(eventID)->startableEvent(quest->getBlueprint());
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
EQuestTypeEnum QuestState_Running::getType() {
	return EQuestTypeEnum::VE_Running;
}
void QuestState_Running::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (int i = 0; i < eventIDs.Num(); i++) {
		UQuestManager::getEvent(eventIDs[i])->startedEvent(quest->getBlueprint());
	}

	testState(quest);
}
TArray<FString> QuestState_Running::getMessages(Quest* quest) {
	return quest->getRunningMessages();
}
void QuestState_Running::testState(Quest* quest) {
	bool isFinished = true;
	bool isFailed = false;

	TArray<QuestTask*> tasks = quest->getTasks();

	for (QuestTask* task : tasks) {
		isFinished = isFinished && task->isComplete();
	}
	
	TArray<QuestTask*> failstates = quest->getFailstates();

	for (QuestTask* fail : failstates) {
		isFailed = isFailed || fail->isComplete();
	}

	if (isFinished) {
		quest->setCurrentState(new QuestState_Completed());
	} else if (isFailed) {
		quest->setCurrentState(new QuestState_Failed());
	}
}
void QuestState_Running::updateTask(Quest* quest, FString id) {
	TArray<QuestTask*> tasks = quest->getTasks();

	for (QuestTask* task : tasks) {
		task->update(id);
	}

	TArray<QuestTask*> failstates = quest->getFailstates();

	for (QuestTask* fail : failstates) {
		fail->update(id);
	}

	testState(quest);
}


//---------------------------------------------------------------------------
//  Completed implementation
//---------------------------------------------------------------------------
EQuestTypeEnum QuestState_Completed::getType() {
	return EQuestTypeEnum::VE_Completed;
}
void QuestState_Completed::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (int i = 0; i < eventIDs.Num(); i++) {
		UQuestManager::getEvent(eventIDs[i])->completedEvent(quest->getBlueprint());
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
EQuestTypeEnum QuestState_ClosedSuccessful::getType() {
	return EQuestTypeEnum::VE_ClosedSuccessful;
}
void QuestState_ClosedSuccessful::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (int i = 0; i < eventIDs.Num(); i++) {
		UQuestManager::getEvent(eventIDs[i])->successfulClosedEvent(quest->getBlueprint());
	}
}
TArray<FString> QuestState_ClosedSuccessful::getMessages(Quest* quest) {
	return quest->getClosedSuccessfulMessages();
}


//---------------------------------------------------------------------------
//  Failed implementation
//---------------------------------------------------------------------------
EQuestTypeEnum QuestState_Failed::getType() {
	return EQuestTypeEnum::VE_Failed;
}
void QuestState_Failed::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (int i = 0; i < eventIDs.Num(); i++) {
		UQuestManager::getEvent(eventIDs[i])->failedEvent(quest->getBlueprint());
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
EQuestTypeEnum QuestState_ClosedFailed::getType() {
	return EQuestTypeEnum::VE_ClosedFailed;
}
void QuestState_ClosedFailed::begin(Quest* quest) {
	TArray<FString> eventIDs = quest->getEventIDs();

	for (int i = 0; i < eventIDs.Num(); i++) {
		UQuestManager::getEvent(eventIDs[i])->failedClosedEvent(quest->getBlueprint());
	}
}
TArray<FString> QuestState_ClosedFailed::getMessages(Quest* quest) {
	return quest->getClosedFailedMessages();
}