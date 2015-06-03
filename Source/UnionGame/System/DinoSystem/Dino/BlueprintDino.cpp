// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "DinoInformation.h"
#include "BlueprintDino.h"

void UBlueprintDino::setDino(DinoInformation* adapter) {
	_adapter = adapter;
}

FString UBlueprintDino::getID() {
	if (_adapter != NULL) {
		return _adapter->getID();
	}
	return "";
}
float UBlueprintDino::getLife() {
	if (_adapter != NULL) {
		return _adapter->getLife();
	}
	return 0.0f;
}
