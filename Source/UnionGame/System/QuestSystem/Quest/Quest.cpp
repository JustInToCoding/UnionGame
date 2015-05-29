// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Quest.h"
#include "BlueprintQuest.h"
#include "QuestState.h"


Quest::Quest() {
	_currentState = new QuestState_NotStartable();

	_redoable = true;

	_tasks.Init(0);
	_eventIDs.Init(0);

	_startingMessages.Init(0);
	_runningMessages.Init(0);
	_completedMessages.Init(0);
	_closedSuccessfulMessages.Init(0);
	_closedFailedMessages.Init(0);

	_wrapper = NewObject<UBlueprintQuest>();
	_wrapper->setQuest(this);
	_wrapper->AddToRoot();
}
Quest::~Quest() {
	_wrapper->setQuest(NULL);
	_wrapper->RemoveFromRoot();
}

void Quest::activate() {
	UE_LOG(LogTemp, Warning, TEXT("Quest activated."));
	_currentState->activate(this);
}
void Quest::trigger() {
	if (_currentState != NULL) {
		_currentState->trigger(this);
	}
}
void Quest::updateTask(FString id) {
	_currentState->updateTask(this, id);
}
void Quest::testState() {
	_currentState->testState(this);
}
TArray<FString> Quest::getMessages() {
	return _currentState->getMessages(this);
}


//-----------------------------------------------------------------------------------
//  Setter
//-----------------------------------------------------------------------------------

void Quest::setID(FString id) {
	_id = id;
}
void Quest::addEventID(FString eventID) {
	_eventIDs.Add(eventID);
}
void Quest::removeEventID() {
	_eventIDs.Reset();
}
void Quest::setRedoable(bool redoaboe) {
	_redoable = redoaboe;
}
void Quest::addTask(QuestTask* task) {
	_tasks.Add(task);
}
void Quest::addFailstate(QuestTask* failID) {
	_failstates.Add(failID);
}
void Quest::setStartingMsg(TArray<FString> msg) {
	_startingMessages = msg;
}
void Quest::setRunningMsg(TArray<FString> msg) {
	_runningMessages = msg;
}
void Quest::setCompletedMsg(TArray<FString> msg) {
	_completedMessages = msg;
}
void Quest::setClosedSuccessfulMsg(TArray<FString> msg) {
	_closedSuccessfulMessages = msg;
}
void Quest::setClosedFailedMsg(TArray<FString> msg) {
	_closedFailedMessages = msg;
}

void Quest::setCurrentState(QuestState* newState) {
	UE_LOG(LogTemp, Warning, TEXT("QuestState updated."));
	
	_currentState = newState;
	_currentState->begin(this);
}

EQuestTypeEnum Quest::getCurrentState() {
	return _currentState->getType();
}