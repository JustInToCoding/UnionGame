// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"

class QuestConverter;
class Quest;

/**
 * 
 */
class UNIONGAME_API QuestTask
{
	friend class QuestConverter;

protected:
	Quest* _main;

public:
	QuestTask(Quest* main);
	~QuestTask();

	virtual void start();
	virtual void update(FString id, int amount);

	virtual bool isComplete();
};

class UNIONGAME_API QuestTask_IDTracker : public QuestTask
{
	friend class QuestConverter;

private:
	FString _ID;
	int _maxCount;
	int _currentCount;

public:
	QuestTask_IDTracker(Quest* main, FString id, int maxCount);
	void update(FString id, int amount);

	bool isComplete();
};

class UNIONGAME_API QuestTask_Timer : public QuestTask
{
	friend class QuestConverter;

private:
	int _time;
	bool _finished;

public:
	QuestTask_Timer(Quest* main, int time);
	void start();
	bool isComplete();
	void timerRunOut();
};

class UNIONGAME_API QuestTask_AND : public QuestTask
{
	friend class QuestConverter;

private:
	TArray<QuestTask*> _tasks;

public:
	QuestTask_AND(Quest* main);
	void start();
	void update(FString id, int amount);

	bool isComplete();
};

class UNIONGAME_API QuestTask_OR : public QuestTask
{
	friend class QuestConverter;

private:
	TArray<QuestTask*> _tasks;

public:
	QuestTask_OR(Quest* main);
	void start();
	void update(FString id, int amount);

	bool isComplete();
};

class UNIONGAME_API QuestTask_NOT : public QuestTask
{
	friend class QuestConverter;

private:
	QuestTask* _task;

public:
	QuestTask_NOT(Quest* main);
	void start();
	void update(FString id, int amount);

	bool isComplete();
};