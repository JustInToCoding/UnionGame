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
	FEntry entry1;
	entry1.id = FString("I01");
	entry1.amount = 1;
	FEntry entry2;
	entry2.id = FString("I02");
	entry2.amount = 2;
	FEntry entry3;
	entry3.id = FString("I03");
	entry3.amount = 3;
	ItemInventory.Add(entry1);
	ItemInventory.Add(entry2);
	ItemInventory.Add(entry3);
}

TArray<FEntry> UInventory::GetCurrentInventory() {
	return ItemInventory;
}

void UInventory::addToInventory(FString id, int32 amount){
	bool alreadyInArray = false;
	for (int i = 0; i < ItemInventory.Num(); i++){
		if (ItemInventory[i].id.Equals(id)){
			ItemInventory[i].amount += amount;
			alreadyInArray = true;
		}
	}
	if (!alreadyInArray){
		FEntry newEntry;
		newEntry.id = id;
		newEntry.amount = amount;
		ItemInventory.Add(newEntry);
	}
}

bool UInventory::removeFromInventory(FString id, int32 amount){
	bool isInInventory = false;
	for (int i = 0; i < ItemInventory.Num(); i++){
		if (ItemInventory[i].id.Equals(id)){
			if (ItemInventory[i].amount >= amount){
				ItemInventory[i].amount -= amount;
				if (ItemInventory[i].amount <= 0){
					ItemInventory.RemoveAt(i);
				}
			}
			else {
				return false;
			}
			isInInventory = true;
		}
	}
	if (!isInInventory){
		return false;
	}
	return true;
}

int32 UInventory::getAmount(FString id){
	int32 amount = 0;
	for (int i = 0; i < ItemInventory.Num(); i++){
		if (ItemInventory[i].id.Equals(id)){
			amount += ItemInventory[i].amount;
		}
	}
	return amount;
}