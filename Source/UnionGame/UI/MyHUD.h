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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool ShowInventory;

	/** Should the Inventory be shown */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool HideHUD;


	UFUNCTION(BlueprintCallable, Category = "Health")
		void setMaxHealth(float health);
	UFUNCTION(BlueprintCallable, Category = "Health")
		void setHealth(float health);
	UFUNCTION(BlueprintCallable, Category = "Stamina")
		void setMaxStamina(float stamina);
	UFUNCTION(BlueprintCallable, Category = "Stamina")
		void setStamina(float stamina);

	/** Main HUD update loop. */
	virtual void DrawHUD() override;

	TOptional<float>		healthPercentage;
	TOptional<float>		staminaPercentage;
	bool InventoryOnScreen = 0;
	bool ShowCrafting = 0;

protected:
	TSharedPtr<class SInventory> InventoryWidget;
	TSharedPtr<class SCrafting> CraftingWidget;
	TSharedPtr<class SPlayerStatus> PlayerStatusWidget;

	float 		health;
	float		stamina;
	float 		maxHealth;
	float		maxStamina;
};

