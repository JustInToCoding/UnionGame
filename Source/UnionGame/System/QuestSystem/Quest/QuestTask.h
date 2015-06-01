// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"

class UBlueprintQuestTask;
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
	UBlueprintQuestTask* _wrapper;

public:
	QuestTask(Quest* main);
	~QuestTask();

	UBlueprintQuestTask* getBlueprint();

	virtual void start();
	virtual void end();
	virtual void update(FString id, int amount);

	virtual bool isComplete();
	virtual bool isWrapperTask();

	virtual void timerRunOut();

	virtual TArray<QuestTask*> getSubTasks();
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

class UNIONGAME_API QuestTask_InventoryTracker : public QuestTask
{
	friend class QuestConverter;

private:
	FString _ID;
	int _maxCount;

public:
	QuestTask_InventoryTracker(Quest* main, FString id, int maxCount);

	bool isComplete();
};

class UNIONGAME_API QuestTask_Timer : public QuestTask
{
	friend class QuestConverter;

private:
	float _time;
	bool _finished;

public:
	QuestTask_Timer(Quest* main, float time);
	void start();
	void end();
	bool isComplete();
	void timerRunOut();
};

class UNIONGAME_API QuestTask_Wrapper : public QuestTask
{
	friend class QuestConverter;
protected:
	TArray<QuestTask*> _tasks;

public:
	QuestTask_Wrapper(Quest* main);

	void start();
	void end();
	bool isWrapperTask();
	void update(FString id, int amount);
};

class UNIONGAME_API QuestTask_AND : public QuestTask_Wrapper
{
public:
	QuestTask_AND(Quest* main);
	bool isComplete();
};

class UNIONGAME_API QuestTask_OR : public QuestTask_Wrapper
{
public:
	QuestTask_OR(Quest* main);
	bool isComplete();
};

class UNIONGAME_API QuestTask_NOT : public QuestTask_Wrapper
{
public:
	QuestTask_NOT(Quest* main);
	bool isComplete();
};