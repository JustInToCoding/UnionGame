// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "BlueprintQuestTask.h"
#include "QuestTask.h"

void UBlueprintQuestTask::timerStart(float time) {
	UWorld* world = _world;
	
	if (world != NULL) {
		world->GetTimerManager().SetTimer(TimerHandle, this, &UBlueprintQuestTask::timerRunOut, time, false);
	}
}
void UBlueprintQuestTask::timerEnd() {
	UWorld* world = _world;

	if (world != NULL) {
		world->GetTimerManager().ClearTimer(TimerHandle);
	}
}
void UBlueprintQuestTask::setWorld(UWorld* world) {
	_world = world;

	if (isWrapperTask()) {
		for (QuestTask* subTask : _adapter->getSubTasks()) {
			if (subTask != NULL)
			{
				UBlueprintQuestTask* BPSub = subTask->getBlueprint();
				if (BPSub != NULL) {
					BPSub->setWorld(world);
				}
			}
		}
	}
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



