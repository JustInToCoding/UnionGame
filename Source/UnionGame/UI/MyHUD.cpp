// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "MyHUD.h"
#include "Widgets/SPlayerStatus.h"
#include "Widgets/Inventory/SInventoryWidget.h"
#include "MyGameResources.h"
#include "Engine.h"

AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	if (HideHUD == true)
	{
		GEngine->GameViewport->RemoveAllViewportWidgets();
		InventoryOnScreen = 0;
	}
	else
	{
		if (PlayerStatusWidget.IsValid())
		{
			GEngine->GameViewport->
				RemoveViewportWidgetContent(PlayerStatusWidget.ToSharedRef());
		}

		if (!PlayerStatusWidget.IsValid())
		{
			SAssignNew(PlayerStatusWidget, SPlayerStatus)
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
}

void AMyHUD::setMaxHealth(float health){
	this->maxHealth = health;
}


void AMyHUD::setHealth(float health){
	this->healthPercentage = health / this->maxHealth;
	this->health = health;
}


void AMyHUD::setMaxStamina(float stamina){
	this->maxStamina = stamina;
}


void AMyHUD::setStamina(float stamina){
	this->staminaPercentage = stamina / this->maxStamina;
	this->stamina = stamina;
}
