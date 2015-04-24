// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "ItemTest.h"
#include "System/ItemSystem/Item.h"
#include "System/ItemSystem/ItemConverter.h"
#include "DynamicData/DDReg.h"


// Sets default values
AItemTest::AItemTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemTest::BeginPlay()
{
	Super::BeginPlay();

	ItemConverter* ic = ItemConverter::getInstance();
	
	/*TArray<DDObject*> items;

	Item* i0 = new Item(0, "Bones", "");
	Item* i1 = new Item(1, "Wood", "");
	Item* i2 = new Item(2, "Lether", "");

	items.Add(i0);
	items.Add(i1);
	items.Add(i2);

	DDReg::save(FPaths::GameDir() + "items.json", items, ic);*/

	TArray<DDObject*> items = DDReg::load(FPaths::GameDir() + "items.json");

	UE_LOG(LogTemp, Warning, TEXT("Items"));

	for (int i = 0; i < items.Num(); i++) {
		Item* item = static_cast<Item*>(items[i]);

		FString msg = "";
		msg.Append("id ").AppendInt(item->getID());
		msg.Append("name ").Append(item->getName());
		msg.Append("desc ").Append(item->getDesc());

		UE_LOG(LogTemp, Warning, TEXT("Item: %s"), *msg);
	}

	UE_LOG(LogTemp, Warning, TEXT("BlaBla"));
}

// Called every frame
void AItemTest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

