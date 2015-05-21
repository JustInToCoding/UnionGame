// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BlueprintQuest.h"
#include "Object.h"

class Quest;

/**
 * 
 */
class UNIONGAME_API QuestState
{
public:
	virtual EQuestTypeEnum getType();
	virtual void begin(Quest* quest);
	virtual void activate(Quest* quest);
	virtual void trigger(Quest* quest);
	virtual void testState(Quest* quest);
	virtual void updateTask(Quest* quest, FString id);
	virtual TArray<FString> getMessages(Quest* quest);
};

class UNIONGAME_API QuestState_NotStartable : public QuestState
{
public:
	EQuestTypeEnum getType();
	void activate(Quest* quest);
};

class UNIONGAME_API QuestState_Startable : public QuestState
{
public:
	EQuestTypeEnum getType();
	void begin(Quest* quest);
	TArray<FString> getMessages(Quest* quest);

	void trigger(Quest* quest);
};

class UNIONGAME_API QuestState_Running : public QuestState
{
public:
	EQuestTypeEnum getType();
	void begin(Quest* quest);
	TArray<FString> getMessages(Quest* quest);

	void testState(Quest* quest);
	void updateTask(Quest* quest, FString id);
};

class UNIONGAME_API QuestState_Completed : public QuestState
{
public:
	EQuestTypeEnum getType();
	void begin(Quest* quest);
	TArray<FString> getMessages(Quest* quest);

	void trigger(Quest* quest);
};

class UNIONGAME_API QuestState_ClosedSuccessful : public QuestState
{
public:
	EQuestTypeEnum getType();
	void begin(Quest* quest);
	TArray<FString> getMessages(Quest* quest);
};

class UNIONGAME_API QuestState_Failed : public QuestState
{
public:
	EQuestTypeEnum getType();
	void begin(Quest* quest);

	void testState(Quest* quest);
};

class UNIONGAME_API QuestState_ClosedFailed : public QuestState
{
public:
	EQuestTypeEnum getType();
	void begin(Quest* quest);
	TArray<FString> getMessages(Quest* quest);
};
