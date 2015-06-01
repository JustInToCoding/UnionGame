// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "BlueprintItem.h"

FString UBlueprintItem::getID(){
	if (item != NULL){
		return item->getID();
	}
	return "";
}
FString UBlueprintItem::getName(){
	if (item != NULL){
		return item->getName();
	}
	return "";
}
FString UBlueprintItem::getDesc(){
	if (item != NULL){
		return item->getDesc();
	}
	return "";
}
FString UBlueprintItem::getSprite(){
	if (item != NULL){
		return item->getSprite();
	}
	return "Gathering sprite failed";
}
