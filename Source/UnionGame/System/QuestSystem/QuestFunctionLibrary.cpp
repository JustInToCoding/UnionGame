// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestFunctionLibrary.h"
#include "QuestTrigger.h"
#include "QuestEvent.h"


void UQuestFunctionLibrary::initQuests() {
	UE_LOG(LogTemp, Warning, TEXT("init"));
	UQuestTrigger* q1t1 = NewObject<UQuestTrigger>();
	_triggerMap.Add("Q1T1", q1t1);

	AQuestEvent* q1e1 = NewObject<AQuestEvent>();
	_eventMap.Add("Q1E1", q1e1);

	q1t1->init(q1e1);
}

UQuestTrigger* UQuestFunctionLibrary::getQuestTrigger(FString id) {
	UE_LOG(LogTemp, Warning, TEXT("Trigger requested: %s"), *id);

	return _triggerMap[id];
}

AQuestEvent* UQuestFunctionLibrary::getQuestEvent(FString id) {
	UE_LOG(LogTemp, Warning, TEXT("Event requested: %s"), *id);

	return _eventMap[id];
}

void UQuestFunctionLibrary::setQuestEvent(FString id, AQuestEvent* qEvent) {
	_eventMap.Add(id, qEvent);
}


TMap<FString, UQuestTrigger*> UQuestFunctionLibrary::_triggerMap;
TMap<FString, AQuestEvent*> UQuestFunctionLibrary::_eventMap;
