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

	for (int i = 0; i < sourceArray.Num(); i++) {
		result.Add(getTask(sourceArray[i], quest));
	}

	return result;
}
QuestTask* QuestConverter::getTask(TSharedPtr<FJsonValue> source, Quest* quest) {
	QuestTask* result = NULL;

	TSharedPtr<FJsonObject> srcObj = source->AsObject();
	if (srcObj->HasField("type")) {
		FString type = srcObj->GetStringField("type");

		UE_LOG(LogTemp, Warning, TEXT("new %s task"), *type);

		if ((FString("counter")).Equals(type)) {
			FString trackedID = srcObj->GetStringField("id");
			int maxCount = srcObj->GetNumberField("count");

			result = new QuestTask_IDTracker(quest, trackedID, maxCount);
		}
		else if ((FString("inventory")).Equals(type)) {
			FString trackedID = srcObj->GetStringField("id");
			int maxCount = srcObj->GetNumberField("count");

			result = new QuestTask_InventoryTracker(quest, trackedID, maxCount);
		}
		else if ((FString("timer")).Equals(type)) {
			int time = srcObj->GetNumberField("time");

			result = new QuestTask_Timer(quest, time);
		}
		else if ((FString("AND")).Equals(type)) {
			TArray<QuestTask*> tasks = getTasks(srcObj->GetArrayField("tasks"), quest);

			result = new QuestTask_AND(quest);

			static_cast<QuestTask_OR*>(result)->_tasks = tasks;
		}
		else if ((FString("OR")).Equals(type)) {
			TArray<QuestTask*> tasks = getTasks(srcObj->GetArrayField("tasks"), quest);

			result = new QuestTask_OR(quest);

			static_cast<QuestTask_OR*>(result)->_tasks = tasks;
		}
		else if ((FString("NOT")).Equals(type)) {
			QuestTask* task = getTask(srcObj->GetObjectField("tasks"), quest);

			result = new QuestTask_NOT(quest);

			static_cast<QuestTask_NOT*>(result)->_task = task;
		}
	}

	return result;
}

TArray<TSharedPtr<FJsonValue>> QuestConverter::getJSONArray(TArray<QuestTask*> sourceArray) {
	TArray<TSharedPtr<FJsonValue>> result;

	for (int i = 0; i < sourceArray.Num(); i++) {
		result.Add(getJSON(sourceArray[i]));
	}

	return result;
}
TSharedPtr<FJsonValue> QuestConverter::getJSON(QuestTask* source) {
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
		result->SetField("task", getJSON(timer->_task));
	}

	return MakeShareable(new FJsonValueObject(result));
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

	QuestTask* task = getTask(value->GetObjectField("tasks"), quest);

	quest->setTask(task);

	QuestTask* failstate = getTask(value->GetObjectField("fails"), quest);

	quest->setFailstate(failstate);

	TArray<FString> tempMsg = getStringArray(value->GetArrayField("StartMsg"));
	quest->setStartingMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField(TEXT("RunningMsg")));
	quest->setRunningMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField(TEXT("CompletedMsg")));
	quest->setCompletedMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField(TEXT("ClosedSuccessfulMsg")));
	quest->setClosedSuccessfulMsg(tempMsg);

	tempMsg = getStringArray(value->GetArrayField(TEXT("ClosedFailedMsg")));
	quest->setClosedFailedMsg(tempMsg);

	return quest;
}

TSharedPtr<FJsonObject> QuestConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	Quest* quest = static_cast<Quest*>(value);

	result->SetStringField(TEXT("id"), quest->getID());
	result->SetBoolField(TEXT("redo"), quest->isRedoable());
	result->SetArrayField(TEXT("events"), getJSONArray(quest->getEventIDs()));
	result->SetField(TEXT("task"), getJSON(quest->getTask()));
	result->SetField(TEXT("fail"), getJSON(quest->getFailstate()));

	result->SetArrayField(TEXT("StartMsg"), getJSONArray(quest->getStartingMessages()));
	result->SetArrayField(TEXT("RunningMsg"), getJSONArray(quest->getRunningMessages()));
	result->SetArrayField(TEXT("CompletedMsg"), getJSONArray(quest->getCompletedMessages()));
	result->SetArrayField(TEXT("ClosedSuccessfulMsg"), getJSONArray(quest->getClosedSuccessfulMessages()));
	result->SetArrayField(TEXT("ClosedFailedMsg"), getJSONArray(quest->getClosedFailedMessages()));

	return result;
}