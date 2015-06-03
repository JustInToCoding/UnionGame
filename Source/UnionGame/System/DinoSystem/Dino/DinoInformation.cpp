// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "DinoInformation.h"
#include "BlueprintDino.h"


DinoInformation::DinoInformation() {
	_wrapper = NewObject<UBlueprintDino>();
	_wrapper->setDino(this);
	_wrapper->AddToRoot();
}
DinoInformation::~DinoInformation() {
	_wrapper->setDino(NULL);
	_wrapper->RemoveFromRoot();
}

//-----------------------------------------------------------------------------------
//  Setter
//-----------------------------------------------------------------------------------

void DinoInformation::setID(FString id) {
	_id = id;
}
void DinoInformation::setLife(float life) {
	_life = life;
}

