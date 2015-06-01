// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FEntry{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = Inventory)
		FString id;
	UPROPERTY(BlueprintReadWrite, Category = Inventory)
		int32 amount;
};

UCLASS(Blueprintable)//config = Game)
class UNIONGAME_API UInventory : public UObject //BlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UInventory(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
	~UInventory();
public:
	UFUNCTION(BlueprintPure, Category = Inventory)
		static UInventory* getInstance();

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "Get Inv", CompactNodeTitle = "GetInv", Keywords = "Get Player Inventory"), Category = Inventory)
		TArray<FEntry> GetCurrentInventory();
	
	UPROPERTY(EditAnywhere, Category = Inventory)
		TArray<FEntry> ItemInventory; // Our Inventory

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void addToInventory(FString id, int32 amount);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		bool removeFromInventory(FString id, int32 amount);

	UFUNCTION(BlueprintPure, Category = Inventory)
		int32 getAmount(FString id);

private:	
	//AInventory(AInventory const&) = delete;
	//void operator=(AInventory const&) const = delete;
	void FillArray();
};
