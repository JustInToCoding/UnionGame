// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../DynamicData/DDConverter.h"
#include "../../../DynamicData/DDObject.h"

class Quest;
class QuestTask;

/**
 * 
 */
class UNIONGAME_API QuestConverter : public DDConverter
{
public:
	static QuestConverter* getInstance();
	~QuestConverter();

protected:
	TArray<QuestTask*> getTasks(TArray<TSharedPtr<FJsonValue>> sourceArray, Quest* quest);
	QuestTask* getTask(TSharedPtr<FJsonValue> source, Quest* quest);

	TArray<TSharedPtr<FJsonValue>> getJSONArray(TArray<QuestTask*> sourceArray);
	TSharedPtr<FJsonValue> getJSON(QuestTask* source);

	TArray<FString> getStringArray(TArray<TSharedPtr<FJsonValue>> sourceArray);
	TArray<TSharedPtr<FJsonValue>> getJSONArray(TArray<FString> sourceArray);
	DDObject* getDDObject(TSharedPtr<FJsonObject> value);
	TSharedPtr<FJsonObject> getJSON(DDObject* value);

private:
	QuestConverter();
};
