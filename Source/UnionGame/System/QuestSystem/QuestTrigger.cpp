// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestTrigger.h"

void UQuestTrigger::activate() {
	_event->OnTriggered();
}
void UQuestTrigger::init(AQuestEvent* qEvent) {
	_event = qEvent;
}


