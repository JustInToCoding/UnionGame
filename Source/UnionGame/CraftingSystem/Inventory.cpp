// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Inventory.h"

AInventory* AInventory::getInstance() {
	static AInventory instance;
	return &instance;
}

AInventory::AInventory(){}

void AInventory::FillArray(){
	//ItemInventory.Add(FString("test"));
	//ItemInventory.Add(FString("test2"));
	//ItemInventory.Add(FString("test3"));
}

TArray<FString> AInventory::GetCurrentInventory() {
	if (&ItemInventory == NULL) {
		TArray<FString>* pTemp = new TArray<FString>();
		ItemInventory = *pTemp;
		FillArray();
	}
	//UE_LOG(LogTemp, Warning, TEXT("%s"), ItemInventory.GetData());
	
	return ItemInventory;
}

FString AInventory::fuckYou(){
	FString FuckYouToo = "Fuck you!";
	return FuckYouToo;
}