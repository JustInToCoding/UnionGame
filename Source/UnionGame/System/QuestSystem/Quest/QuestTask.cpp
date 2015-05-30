// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestTask.h"
#include "Quest.h"
#include "../../InventorySystem/Inventory.h"

//---------------------------------------------------------------------------
//  Default implementation
//---------------------------------------------------------------------------
QuestTask::~QuestTask() {

}
QuestTask::QuestTask(Quest* main) {
	_main = main;
}

void QuestTask::start() {
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
QuestTask_Timer::QuestTask_Timer(Quest* main, int time) : QuestTask(main) {
	_time = time;
	_finished = false;
}
void QuestTask_Timer::start() {
	FTimerHandle ThisTimerHandle;
	_main->getBlueprint()
		 ->GetWorld()
		 ->GetTimerManager().SetTimer(ThisTimerHandle, this, &QuestTask_Timer::timerRunOut, _time);
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
}
bool QuestTask_Wrapper::isWrapperTask() {
	return true;
}

//---------------------------------------------------------------------------
//  AND implementation
//---------------------------------------------------------------------------
QuestTask_AND::QuestTask_AND(Quest* main) : QuestTask_Wrapper(main) {
	_tasks.Init(0);
}
void QuestTask_AND::start() {
	for (QuestTask* task : _tasks) {
		task->start();
	}
}
bool QuestTask_AND::isComplete() {
	bool finished = true;

	for (QuestTask* task : _tasks) {
		finished = finished && task->isComplete();
	}

	return finished;
}
void QuestTask_AND::update(FString id, int amount) {
	for (QuestTask* task : _tasks) {
		task->update(id, amount);
	}
}

//---------------------------------------------------------------------------
//  OR implementation
//---------------------------------------------------------------------------
QuestTask_OR::QuestTask_OR(Quest* main) : QuestTask_Wrapper(main) {
	_tasks.Init(0);
}
void QuestTask_OR::start() {
	for (QuestTask* task : _tasks) {
		task->start();
	}
}
bool QuestTask_OR::isComplete() {
	bool finished = false;

	for (QuestTask* task : _tasks) {
		finished = finished || task->isComplete();
	}

	return finished;
}
void QuestTask_OR::update(FString id, int amount) {
	for (QuestTask* task : _tasks) {
		task->update(id, amount);
	}
}

//---------------------------------------------------------------------------
//  NOT implementation
//---------------------------------------------------------------------------
QuestTask_NOT::QuestTask_NOT(Quest* main) : QuestTask_Wrapper(main) {
}
void QuestTask_NOT::start() {
	if (_task != NULL) {
		_task->start();
	}
}
bool QuestTask_NOT::isComplete() {
	bool finished = true;

	if (_task != NULL) {
		finished = !_task->isComplete();
	}

	return finished;
}
void QuestTask_NOT::update(FString id, int amount) {
	if (_task != NULL) {
		_task->update(id, amount);
	}
}