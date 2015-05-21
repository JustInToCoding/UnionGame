// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "RecipeTest.h"
#include "System/CraftingSystem/Recipe.h"
#include "System/CraftingSystem/RecipeConverter.h"
#include "System/InventorySystem/Inventory.h"
#include "DynamicData/DDReg.h"


// Sets default values
ARecipeTest::ARecipeTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARecipeTest::BeginPlay()
{
	Super::BeginPlay();
	LoadRecipes();
	SaveRecipes();
}

// Called every frame
void ARecipeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARecipeTest::LoadRecipes(){
	RecipeConverter* rc = RecipeConverter::getInstance();
	TArray<DDObject*> recipes = DDReg::load(FPaths::GameDir() + "Recipes.json");
	UE_LOG(LogTemp, Warning, TEXT("Recipes: "));

	for (int i = 0; i < recipes.Num(); i++) {
		Recipe* recipe = static_cast<Recipe*>(recipes[i]);

		FString msg = recipe->toString();

		UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
	}
}

void ARecipeTest::SaveRecipes(){
	RecipeConverter* rc = RecipeConverter::getInstance();

	TArray<DDObject*> recipes;
	FEntry* item1 = new FEntry(), *item2 = new FEntry(), *gives = new FEntry();
	TArray<FEntry*> needs;

	item1->id = TEXT("I01");
	item1->amount = 1;
	item2->id = TEXT("I02");
	item2->amount = 1;
	gives->id = TEXT("I03");
	gives->amount = 1;

	needs.Add(item1);
	needs.Add(item2);

	Recipe* r0 = new Recipe(TEXT("R01"), needs, gives);

	recipes.Add(r0);

	DDReg::save(FPaths::GameDir() + "recipesSaveTest.json", recipes, rc);

	UE_LOG(LogTemp, Warning, TEXT("Saved recipes: "));

	for (int i = 0; i < recipes.Num(); i++) {
		Recipe* recipe = static_cast<Recipe*>(recipes[i]);

		FString msg = recipe->toString();

		UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
	}
}
