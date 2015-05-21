// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Quest.h"
#include "BlueprintQuest.h"


void UBlueprintQuest::setQuest(Quest* adapter) {
	_adapter = adapter;
}

void UBlueprintQuest::activate() {
	UE_LOG(LogTemp, Warning, TEXT("BPQuest activated."));
	
	_adapter->activate();
}
void UBlueprintQuest::trigger() {
	_adapter->trigger();
}
void UBlueprintQuest::updateTask(FString id) {
	_adapter->updateTask(id);
}
TArray<FString> UBlueprintQuest::getMessages() {
	return _adapter->getMessages();
}

void UBlueprintQuest::addEventID(FString eventID) {
	_adapter->addEventID(eventID);
}

EQuestTypeEnum UBlueprintQuest::getCurrentState() {
	return _adapter->getCurrentState();
}

FString UBlueprintQuest::getID() { return _adapter->getID(); }
TArray<FString> UBlueprintQuest::getEventIDs() { return _adapter->getEventIDs(); }
bool UBlueprintQuest::isRedoable() { return _adapter->isRedoable(); }
