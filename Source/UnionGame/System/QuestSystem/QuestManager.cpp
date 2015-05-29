// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "QuestManager.h"
#include "../../DynamicData/DDReg.h"
#include "Quest/QuestConverter.h"
#include "Quest/BlueprintQuest.h"
#include "Quest/Quest.h"
#include "QuestEvent.h"

//Event
void UQuestManager::registerEvent(TSubclassOf<UQuestEvent> questEventClass, FString id) {
	_eventsMap.Add(id, ConstructObject<UQuestEvent>(questEventClass));
}
UQuestEvent* UQuestManager::getEvent(FString id) {
	return _eventsMap[id];
}

//Quest
void UQuestManager::loadQuests(FString file) {
	QuestConverter* converter = QuestConverter::getInstance();

	TArray<DDObject*> loaded = DDReg::load(FPaths::GameDir() + file);

	for (DDObject* ddo : loaded) {
		Quest* quest = static_cast<Quest*>(ddo);
		
		_questsMap.Add(quest->getID(), quest->getBlueprint());
	}
}
UBlueprintQuest* UQuestManager::getQuest(FString id) {
	UBlueprintQuest* quest = NULL;
	
	if (_questsMap.Contains(id)) {
		quest = _questsMap[id];
	}

	if (quest == NULL) {
		quest = NewObject<UBlueprintQuest>();
	}

	return quest;
}

void UQuestManager::activate(FString questID) {
	UBlueprintQuest* quest = getQuest(questID);

	quest->activate();
}
void UQuestManager::update(FString id, int32 amount) {
	TArray<FString> keys;

	_questsMap.GetKeys(keys);

	for (FString key : keys) {
		UBlueprintQuest* quest = _questsMap[key];

		quest->updateTask(id, amount);
	}
}

TMap<FString, UBlueprintQuest*> UQuestManager::_questsMap;
TMap<FString, UQuestEvent*> UQuestManager::_eventsMap;
