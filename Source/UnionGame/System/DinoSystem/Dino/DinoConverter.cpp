// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "DinoConverter.h"
#include "DinoInformation.h"
#include "../../../DynamicData/DDReg.h"

DinoConverter* DinoConverter::getInstance() {
	static DinoConverter instance;
	static bool isInReg = false;

	if (!isInReg) {
		DDReg::reg(&instance);
	}

	return &instance;
}
DinoConverter::DinoConverter() : DDConverter("DinoConverter") {
}

DinoConverter::~DinoConverter() {
}

DDObject* DinoConverter::getDDObject(TSharedPtr<FJsonObject> value) {
	DinoInformation* dino = new DinoInformation();

	dino->setID(value->GetStringField("id"));
	dino->setLife(value->GetNumberField("life"));

	return dino;
}

TSharedPtr<FJsonObject> DinoConverter::getJSON(DDObject* value) {
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	DinoInformation* dino = static_cast<DinoInformation*>(value);

	result->SetStringField("id", dino->getID());
	result->SetNumberField("life", dino->getLife());

	return result;
}