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
void QuestTask::update(FString id) {
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
	UE_LOG(LogTemp, Warning, TEXT("new ID Tracker Task"));
	_ID = id;
	_maxCount = maxCount;
	_currentCount = 0;
}
void QuestTask_IDTracker::update(FString id) {
	UE_LOG(LogTemp, Warning, TEXT("update Task"));
	if (_ID.Equals(id)) {
		UE_LOG(LogTemp, Warning, TEXT("  yap"));
		_currentCount++;
	}
}

bool QuestTask_IDTracker::isComplete() {
	return _currentCount >= _maxCount;
}


//---------------------------------------------------------------------------
//  Timer implementation
//---------------------------------------------------------------------------
QuestTask_Timer::QuestTask_Timer(Quest* main, int time) : QuestTask(main) {
	UE_LOG(LogTemp, Warning, TEXT("new ID Timer Task"));
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
