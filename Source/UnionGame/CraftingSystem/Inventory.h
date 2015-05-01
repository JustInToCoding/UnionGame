// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Kismet/BlueprintFunctionLibrary.h"
#include "Inventory.generated.h"

UCLASS(Blueprintable)//config = Game)
class UNIONGAME_API AInventory : public AActor //BlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = Inventory)
		static AInventory* getInstance();

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "Get Inv", CompactNodeTitle = "GetInv", Keywords = "Get Player Inventory"), Category = Inventory)
		TArray<FString> GetCurrentInventory();
	
	UPROPERTY(EditAnywhere, Category = Inventory)
		TArray<FString> ItemInventory; // Our Inventory

	UFUNCTION(BlueprintPure, Category = Inventory)
		FString fuckYou();

private:
	AInventory();
	//AInventory(AInventory const&) = delete;
	//void operator=(AInventory const&) const = delete;
	void FillArray();
};
