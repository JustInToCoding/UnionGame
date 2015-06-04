// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"


/**
*
*/
UCLASS()
class AMyHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/** Should the Inventory be shown */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	bool ShowInventory;

	/** Main HUD update loop. */
	virtual void DrawHUD() override;


protected:
	void DrawMainHUD();

	float 		MaxValue;
	float 		Value;

	bool InventoryOnScreen = 0;

	TSharedPtr<class SInventoryWidget> InventoryWidget;
	TSharedPtr<class SPlayerStatus> PlayerStatusWidget;

};

