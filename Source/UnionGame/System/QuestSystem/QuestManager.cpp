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
	UQuestEvent* newEventHandler = ConstructObject<UQuestEvent>(questEventClass);
	newEventHandler->AddToRoot();

	_eventsMap.Add(id, newEventHandler);
}
UQuestEvent* UQuestManager::getEvent(FString id) {
	UQuestEvent* result = NULL;

	if (_eventsMap.Contains(id)) {
		result = _eventsMap[id];
	}

	return result;
}

//Quest
void UQuestManager::loadQuests(FString file, AActor* worldSource) {
	UE_LOG(LogQuestSystem, Log, TEXT("start loading quests"));
	QuestConverter* converter = QuestConverter::getInstance();

	TArray<DDObject*> loaded = DDReg::load(FPaths::GameDir() + file);

	if (loaded.Num() <= 0) {
		UE_LOG(LogQuestSystem, Error, TEXT("No Quests have been loaded."));
		UE_LOG(LogQuestSystem, Error, TEXT("  This might be because of errors in the JSON-File."));
		UE_LOG(LogQuestSystem, Error, TEXT("  Check if there are missplaced commas, brackets or tags."));
	}

	for (DDObject* ddo : loaded) {
		Quest* quest = static_cast<Quest*>(ddo);
		UE_LOG(LogQuestSystem, Log, TEXT("  quests %s"), *quest->getID());
		
		if (quest != NULL) {
			UBlueprintQuest* bpQuest = quest->getBlueprint();

			bpQuest->setWorld(worldSource->GetWorld());

			_questsMap.Add(quest->getID(), quest->getBlueprint());
		}
	}
	UE_LOG(LogQuestSystem, Log, TEXT("end loading quests"));
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
