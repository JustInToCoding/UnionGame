// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "MyHUD.h"
#include "Widgets/SPlayerStatus.h"
#include "Widgets/Inventory/SInventoryWidget.h"
#include "MyGameResources.h"
#include "Engine.h"

AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxValue = 2000.0f;
	Value = 1000.0f;
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	if (PlayerStatusWidget.IsValid())
	{
		GEngine->GameViewport->
			RemoveViewportWidgetContent(PlayerStatusWidget.ToSharedRef());
	}

	if (!PlayerStatusWidget.IsValid())
	{
		SAssignNew(PlayerStatusWidget, SPlayerStatus)
			.HealthValue(Value)
			.HealthMaxValue(MaxValue)
			.StaminaValue(Value)
			.StaminaMaxValue(MaxValue)
			.OwnerHUD(this);
	}
	else
	{
		GEngine->GameViewport->
			AddViewportWidgetContent(PlayerStatusWidget.ToSharedRef());
	}

	if (ShowInventory == true)
	{
		if (!InventoryWidget.IsValid())
		{
			SAssignNew(InventoryWidget, SInventoryWidget)
				.OwnerHUD(this);			
		}
		else if (InventoryOnScreen == 0)
		{
			GEngine->GameViewport->
				AddViewportWidgetContent(InventoryWidget.ToSharedRef());
			InventoryOnScreen = 1;
			
		}
	}
	else
	{
		if (InventoryWidget.IsValid())
		{
			GEngine->GameViewport->
				RemoveViewportWidgetContent(InventoryWidget.ToSharedRef());
			InventoryOnScreen = 0;
		}
	}
}