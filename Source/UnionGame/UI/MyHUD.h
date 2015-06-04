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


private:
	float 		maxHealth;
	float 		health;
	float		maxStamina;
	float		stamina;

	bool InventoryOnScreen = 0;

	TSharedPtr<class SInventoryWidget> InventoryWidget;
	TSharedPtr<class SPlayerStatus> PlayerStatusWidget;
public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void setMaxHealth(float health);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void setHealth(float health);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void setMaxStamina(float stamina);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void setStamina(float stamina);
};

