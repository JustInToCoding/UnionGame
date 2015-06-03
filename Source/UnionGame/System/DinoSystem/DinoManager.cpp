// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "DinoManager.h"
#include "../../DynamicData/DDReg.h"
#include "Dino/DinoConverter.h"
#include "Dino/BlueprintDino.h"
#include "Dino/DinoInformation.h"

//Quest
void UDinoManager::loadDinos() {
	UE_LOG(LogDinoSystem, Log, TEXT("start loading dinos"));
	DinoConverter* converter = DinoConverter::getInstance();

	TArray<DDObject*> loaded = DDReg::load("dinos");

	if (loaded.Num() <= 0) {
		UE_LOG(LogDinoSystem, Error, TEXT("No dinos have been loaded."));
		UE_LOG(LogDinoSystem, Error, TEXT("  This might be because of errors in the JSON-File."));
		UE_LOG(LogDinoSystem, Error, TEXT("  Check if there are missplaced commas, brackets or tags."));
	}

	for (DDObject* ddo : loaded) {
		DinoInformation* dino = static_cast<DinoInformation*>(ddo);
		UE_LOG(LogDinoSystem, Log, TEXT("  dino %s"), *dino->getID());

		if (dino != NULL) {
			_dinosMap.Add(dino->getID(), dino->getBlueprint());
		}
	}
	UE_LOG(LogDinoSystem, Log, TEXT("end loading dinos"));
}
UBlueprintDino* UDinoManager::getDino(FString id) {
	UBlueprintDino* dino = NULL;

	if (_dinosMap.Contains(id)) {
		dino = _dinosMap[id];
	}

	if (dino == NULL) {
		dino = NewObject<UBlueprintDino>();
	}

	return dino;
}

TMap<FString, UBlueprintDino*> UDinoManager::_dinosMap;





