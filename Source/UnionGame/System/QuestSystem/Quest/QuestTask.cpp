// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestTask.h"
#include "Quest.h"

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
//  Timer implementation
//---------------------------------------------------------------------------
QuestTask_Timer::QuestTask_Timer(Quest* main, int time) : QuestTask(main) {
	_time = time;
	_finished = false;
}
void QuestTask_Timer::start() {
	/*FTimerHandle ThisTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ThisTimerHandle, this, &QuestTask_Timer::timerRunOut, _time);*/
}
bool QuestTask_Timer::isComplete() {
	return _finished;
}
void QuestTask_Timer::timerRunOut() {
	_finished = true;
	_main->testState();
}
