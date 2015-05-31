// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "BlueprintQuestTask.h"
#include "QuestTask.h"

void UBlueprintQuestTask::timerStart(int time) {
	FTimerHandle ThisTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ThisTimerHandle, this, &UBlueprintQuestTask::timerRunOut, time);
}
void UBlueprintQuestTask::timerRunOut() {
	if (_adapter != NULL) {
		_adapter->timerRunOut();
	}
}
QuestTask* UBlueprintQuestTask::getTask() {
	return _adapter;
}
void UBlueprintQuestTask::start() {
	if (_adapter != NULL) {
		_adapter->start();
	}
}
void UBlueprintQuestTask::update(FString id, int32 amount) {
	if (_adapter != NULL) {
		_adapter->update(id, amount);
	}
}
bool UBlueprintQuestTask::isComplete() {
	bool result = false;

	if (_adapter != NULL) {
		result = _adapter->isComplete();
	}

	return result;
}
bool UBlueprintQuestTask::isWrapperTask() {
	bool result = false;

	if (_adapter != NULL) {
		result = _adapter->isWrapperTask();
	}

	return result;
}



