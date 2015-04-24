// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNIONGAME_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	/** Variable for storing the font */
	UPROPERTY()
	UFont* HUDFont;

	/**Declaration of the constructor */
	AMyHUD(const FObjectInitializer& ObjectInitializer);

	/**Primary draw call for the HUD */
	virtual void DrawHUD() override;
	
};
