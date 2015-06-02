// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestConverter.h"
#include "Quest.h"
#include "../../../DynamicData/DDReg.h"

QuestConverter* QuestConverter::getInstance() {
	static QuestConverter instance;
	static bool isInReg = false;

	if (!isInReg) {
		DDReg::reg(&instance);
	}

	return &instance;
}
QuestConverter::QuestConverter() : DDConverter("QuestConverter") {
}

QuestConverter::~QuestConverter() {
}

TArray<QuestTask*> QuestConverter::getTasks(TArray<TSharedPtr<FJsonValue>> sourceArray, Quest* quest) {
	TArray<QuestTask*> result;

	result.Init(0);

	TSharedPtr<FJsonObject> temp;

	for (TSharedPtr<FJsonValue> value : sourceArray) {
		temp = value->AsObject();
		result.Add(getTask(temp, quest));
	}

	return result;
}
QuestTask* QuestConverter::getTask(TSharedPtr<FJsonObject> source, Quest* quest) {
	QuestTask* result = NULL;

	if (source->HasField("type")) {
		FString type = source->GetStringField("type");

		UE_LOG(LogJsonSystem, Log, TEXT("new %s task"), *type);

		if ((FString("counter")).Equals(type)) {
			FString trackedID = source->GetStringField("id");
			int maxCount = source->GetNumberField("count");

			result = new QuestTask_IDTracker(quest, trackedID, maxCount);
		}
		else if ((FString("inventory")).Equals(type)) {
			FString trackedID = source->GetStringField("id");
			int maxCount = source->GetNumberField("count");

			result = new QuestTask_InventoryTracker(quest, trackedID, maxCount);
		}
		else if ((FString("timer")).Equals(type)) {
			float time = source->GetNumberField("time");

			result = new QuestTask_Timer(quest, time);
		}
		else if ((FString("AND")).Equals(type)) {
			TArray<QuestTask*> tasks = getTasks(source->GetArrayField("tasks"), quest);

			result = new QuestTask_AND(quest);

			static_cast<QuestTask_Wrapper*>(result)->_tasks = tasks;
		}
		else if ((FString("OR")).Equals(type)) {
			TArray<QuestTask*> tasks = getTasks(source->GetArrayField("tasks"), quest);

			result = new QuestTask_OR(quest);

			static_cast<QuestTask_Wrapper*>(result)->_tasks = tasks;
		}
		else if ((FString("NOT")).Equals(type)) {
			TArray<QuestTask*> tasks = getTasks(source->GetArrayField("tasks"), quest);

			result = new QuestTask_NOT(quest);

			static_cast<QuestTask_Wrapper*>(result)->_tasks = tasks;
		}
	}

	return result;
}

TArray<TSharedPtr<FJsonValue>> QuestConverter::getJSONArray(TArray<QuestTask*> sourceArray) {
	TArray<TSharedPtr<FJsonValue>> result;

	result.Init(0);

	TSharedPtr<FJsonObject> temp;
	TSharedPtr<FJsonValue> value;

	for (int i = 0; i < sourceArray.Num(); i++) {
		temp = getJSON(sourceArray[i]);
		value = MakeShareable(new FJsonValueObject(temp));
		result.Add(value);
	}

	return result;
}
TSharedPtr<FJsonObject> QuestConverter::getJSON(QuestTask* source) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	if (QuestTask_IDTracker* tracker = static_cast<QuestTask_IDTracker*>(source)) {
		result->SetStringField("type", "count");
		result->SetStringField("id", tracker->_ID);
		result->SetNumberField("count", tracker->_maxCount);
	}
	else if (QuestTask_InventoryTracker* tracker = static_cast<QuestTask_InventoryTracker*>(source)) {
		result->SetStringField("type", "inventory");
		result->SetStringField("id", tracker->_ID);
		result->SetNumberField("count", tracker->_maxCount);
	}
	else if (QuestTask_Timer* timer = static_cast<QuestTask_Timer*>(source)) {
		result->SetStringField("type", "count");
		result->SetNumberField("time", timer->_time);
	}
	else if (QuestTask_AND* timer = static_cast<QuestTask_AND*>(source)) {
		result->SetStringField("type", "AND");
		result->SetArrayField("tasks", getJSONArray(timer->_tasks));
	}
	else if (QuestTask_OR* timer = static_cast<QuestTask_OR*>(source)) {
		result->SetStringField("type", "OR");
		result->SetArrayField("tasks", getJSONArray(timer->_tasks));
	}
	else if (QuestTask_NOT* timer = static_cast<QuestTask_NOT*>(source)) {
		result->SetStringField("type", "NOT");
		result->SetObjectField("task", getJSON(timer->_tasks[0]));
	}

	return result;
}


TArray<FString> QuestConverter::getStringArray(TArray<TSharedPtr<FJsonValue>> sourceArray) {
	TArray<FString> result;

	for (int i = 0; i < sourceArray.Num(); i++) {
		result.Add(sourceArray[i]->AsString());
	}

	return result;
}
TArray<TSharedPtr<FJsonValue>> QuestConverter::getJSONArray(TArray<FString> sourceArray) {
	TArray<TSharedPtr<FJsonValue>> result;

	FJsonValueString* temp;
	for (int i = 0; i < sourceArray.Num(); i++) {
		temp = new FJsonValueString(sourceArray[i]);
		result.Add(MakeShareable(temp));
	}

	return result;
}
DDObject* QuestConverter::getDDObject(TSharedPtr<FJsonObject> value) {
	Quest* quest = new Quest();

	quest->setID(value->GetStringField("id"));
	quest->setRedoable(value->GetBoolField("redo"));

	TArray<FString> eventIDs = getStringArray(value->GetArrayField("events"));

	for (int i = 0; i < eventIDs.Num(); i++) {
		quest->addEventID(eventIDs[i]);
	}

	QuestTask* task = getTask(value->GetObjectField("task"), quest);

	quest->setTask(task);

	QuestTask* failstate = getTask(value->GetObjectField("fail"), quest);

	quest->setFailstate(failstate);

	TArray<FString> tempMsg = getStringArray(value->GetArrayField("StartMsg"));
	quest->setStartingMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField("RunningMsg"));
	quest->setRunningMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField("CompletedMsg"));
	quest->setCompletedMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField("ClosedSuccessfulMsg"));
	quest->setClosedSuccessfulMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField("ClosedFailedMsg"));
	quest->setClosedFailedMsg(tempMsg);

	return quest;
}

TSharedPtr<FJsonObject> QuestConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	Quest* quest = static_cast<Quest*>(value);

	result->SetStringField("id", quest->getID());
	result->SetBoolField("redo", quest->isRedoable());
	result->SetArrayField("events", getJSONArray(quest->getEventIDs()));
	result->SetObjectField("task", getJSON(quest->getTask()));
	result->SetObjectField("fail", getJSON(quest->getFailstate()));

	result->SetArrayField("StartMsg", getJSONArray(quest->getStartingMessages()));
	result->SetArrayField("RunningMsg", getJSONArray(quest->getRunningMessages()));
	result->SetArrayField("CompletedMsg", getJSONArray(quest->getCompletedMessages()));
	result->SetArrayField("ClosedSuccessfulMsg", getJSONArray(quest->getClosedSuccessfulMessages()));
	result->SetArrayField("ClosedFailedMsg", getJSONArray(quest->getClosedFailedMessages()));

	return result;
}