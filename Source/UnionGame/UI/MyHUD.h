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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called as soon as game starts, create SCompoundWidget and give Viewport access
	virtual void DrawHUD() override;
	void DrawHUD_DrawMainInfo();
	void DrawHUD_Reset();

private:
	float 		MaxValue;
	float 		Value;

	bool InventoryOnScreen = 0;

	TSharedPtr<class SInventoryWidget> InventoryWidget;

};

