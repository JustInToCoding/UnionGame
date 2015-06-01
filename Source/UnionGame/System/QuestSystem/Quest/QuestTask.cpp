// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestTask.h"
#include "Quest.h"
#include "BlueprintQuestTask.h"
#include "../../InventorySystem/Inventory.h"

//---------------------------------------------------------------------------
//  Default implementation
//---------------------------------------------------------------------------
QuestTask::~QuestTask() {

}
QuestTask::QuestTask(Quest* main) {
	_main = main;

	_wrapper = NewObject<UBlueprintQuestTask>();
	_wrapper->_adapter = this;
	_wrapper->AddToRoot();
}

UBlueprintQuestTask* QuestTask::getBlueprint() {
	return _wrapper;
}

void QuestTask::start() {
	//There is no default implementation
}
void QuestTask::end() {
	//There is no default implementation
}
void QuestTask::update(FString id, int amount) {
	//There is no default implementation
}

bool QuestTask::isComplete() {
	//There is no default implementation
	return true;
}

bool QuestTask::isWrapperTask() {
	return false;
}

void QuestTask::timerRunOut() {
	//There is no default implementation
}

TArray<QuestTask*> QuestTask::getSubTasks() {
	TArray<QuestTask*> result;

	result.Init(0);

	return result;
}

//---------------------------------------------------------------------------
//  IDTracker implementation
//---------------------------------------------------------------------------
QuestTask_IDTracker::QuestTask_IDTracker(Quest* main, FString id, int maxCount) : QuestTask(main) {
	_ID = id;
	_maxCount = maxCount;
	_currentCount = 0;
}
void QuestTask_IDTracker::update(FString id, int amount) {
	if (_ID.Equals(id) && amount > 0) {
		_currentCount += amount;
	}
}

bool QuestTask_IDTracker::isComplete() {
	return _currentCount >= _maxCount;
}

//---------------------------------------------------------------------------
//  InventoryTracker implementation
//---------------------------------------------------------------------------
QuestTask_InventoryTracker::QuestTask_InventoryTracker(Quest* main, FString id, int maxCount) : QuestTask(main) {
	_ID = id;
	_maxCount = maxCount;
}

bool QuestTask_InventoryTracker::isComplete() {
	int currentCount = 0;

	currentCount = UInventory::getInstance()->getAmount(_ID);

	return currentCount >= _maxCount;
}

//---------------------------------------------------------------------------
//  Timer implementation
//---------------------------------------------------------------------------
QuestTask_Timer::QuestTask_Timer(Quest* main, float time) : QuestTask(main) {
	_time = time;
	_finished = false;
}
void QuestTask_Timer::start() {
	_finished = false;
	getBlueprint()->timerStart(_time);
}
void QuestTask_Timer::end() {
	getBlueprint()->timerEnd();
}
bool QuestTask_Timer::isComplete() {
	return _finished;
}
void QuestTask_Timer::timerRunOut() {
	_finished = true;
	_main->testState();
}

//---------------------------------------------------------------------------
//  Warapper implementation
//---------------------------------------------------------------------------
QuestTask_Wrapper::QuestTask_Wrapper(Quest* main) : QuestTask(main) {
	_tasks.Init(0);
}
void QuestTask_Wrapper::start() {
	for (QuestTask* task : _tasks) {
		task->start();
	}
}
void QuestTask_Wrapper::end() {
	for (QuestTask* task : _tasks) {
		task->end();
	}
}
bool QuestTask_Wrapper::isWrapperTask() {
	return true;
}
void QuestTask_Wrapper::update(FString id, int amount) {
	for (QuestTask* task : _tasks) {
		task->update(id, amount);
	}
}

//---------------------------------------------------------------------------
//  AND implementation
//---------------------------------------------------------------------------
QuestTask_AND::QuestTask_AND(Quest* main) : QuestTask_Wrapper(main) {
}
bool QuestTask_AND::isComplete() {
	bool finished = true;

	for (QuestTask* task : _tasks) {
		finished = finished && task->isComplete();
	}

	return finished;
}

//---------------------------------------------------------------------------
//  OR implementation
//---------------------------------------------------------------------------
QuestTask_OR::QuestTask_OR(Quest* main) : QuestTask_Wrapper(main) {
}
bool QuestTask_OR::isComplete() {
	bool finished = false;

	for (QuestTask* task : _tasks) {
		finished = finished || task->isComplete();
	}

	return finished;
}

//---------------------------------------------------------------------------
//  NOT implementation
//---------------------------------------------------------------------------
QuestTask_NOT::QuestTask_NOT(Quest* main) : QuestTask_Wrapper(main) {
}
bool QuestTask_NOT::isComplete() {
	bool finished = true;

	if (_tasks.Num() >= 0) {
		finished = !_tasks[0]->isComplete();
	}

	return finished;
}
