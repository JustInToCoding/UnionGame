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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxValue;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Reference to an SCompoundWidget, TSharedPtr adds to the refcount of MyUIWidget
	/////MyUIWidget will not self-destruct as long as refcount > 0
	/////MyUIWidget refcount will be (refcout-1) if HUD is destroyed.
	TSharedPtr<class SResourceBar> HealthBar;
	TSharedPtr<class SResourceBar> StaminaBar;


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called as soon as game starts, create SCompoundWidget and give Viewport access
	virtual void DrawHUD() override;
	void DrawHUD_DrawMainInfo();

};

