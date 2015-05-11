// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Inventory.h"

UInventory* UInventory::getInstance() {
	static UInventory* instance = NewObject<UInventory>();
	return instance;
}

UInventory::UInventory(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer){
	AddToRoot();
	ItemInventory.Init(0);
	FillArray();
}

UInventory::~UInventory(){}

void UInventory::FillArray(){
	ItemInventory.Add(FString("test"));
	ItemInventory.Add(FString("test2"));
	ItemInventory.Add(FString("test3"));
}

TArray<FString> UInventory::GetCurrentInventory() {
	return ItemInventory;
}