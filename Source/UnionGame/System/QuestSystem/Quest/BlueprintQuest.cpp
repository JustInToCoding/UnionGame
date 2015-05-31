// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Quest.h"
#include "QuestTask.h"
#include "BlueprintQuest.h"
#include "BlueprintQuestTask.h"

void UBlueprintQuest::setQuest(Quest* adapter) {
	_adapter = adapter;
}

void UBlueprintQuest::activate() {
	if (_adapter != NULL) {
		_adapter->activate();
	}
}
void UBlueprintQuest::trigger() {
	if (_adapter != NULL) {
		_adapter->trigger();
	}
}
void UBlueprintQuest::updateTask(FString id, int32 amount) {
	if (_adapter != NULL) {
		_adapter->updateTask(id, amount);
	}
}
TArray<FString> UBlueprintQuest::getMessages() {
	if (_adapter != NULL) {
		return _adapter->getMessages();
	}
	TArray<FString> temp;

	return temp;
}

void UBlueprintQuest::addEventID(FString eventID) {
	if (_adapter != NULL) {
		_adapter->addEventID(eventID);
	}
}
UBlueprintQuestTask* UBlueprintQuest::getTask() {
	UBlueprintQuestTask* result = NewObject<UBlueprintQuestTask>();

	if (_adapter != NULL) {
		result = _adapter->getTask()->getBlueprint();
	}

	return result;
}
UBlueprintQuestTask* UBlueprintQuest::getFailstate() {
	UBlueprintQuestTask* result = NewObject<UBlueprintQuestTask>();

	if (_adapter != NULL) {
		result = _adapter->getFailstate()->getBlueprint();
	}

	return result;
}

EQuestTypeEnum UBlueprintQuest::getCurrentState() {
	if (_adapter != NULL) {
		return _adapter->getCurrentState();
	}

	return EQuestTypeEnum::VE_NotStartable;
}

FString UBlueprintQuest::getID() {
	if (_adapter != NULL) {
		return _adapter->getID();
	}
	return "";
}
TArray<FString> UBlueprintQuest::getEventIDs() {
	if (_adapter != NULL) {
		return _adapter->getEventIDs();
	}
	TArray<FString> temp;

	return temp;
}
bool UBlueprintQuest::isRedoable() { 
	if (_adapter != NULL) {
		return _adapter->isRedoable();
	}
	return false;
}
