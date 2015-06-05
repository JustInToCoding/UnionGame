// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MyHUD.h"
#include "Slate.h"

/**
 * 
 */
class UNIONGAME_API SPlayerStatus : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPlayerStatus)
	{}
		SLATE_ATTRIBUTE(float, HealthMaxValue)
		SLATE_ATTRIBUTE(float, HealthValue)
		SLATE_ATTRIBUTE(float, StaminaMaxValue)
		SLATE_ATTRIBUTE(float, StaminaValue)

		SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

		TOptional<float> getHealthPercentage() const;
		TOptional<float> getStaminaPercentage() const;

protected:
	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	TAttribute<float> HealthMaxValue;
	TAttribute<float> HealthValue;
	TAttribute<float> StaminaMaxValue;
	TAttribute<float> StaminaValue;
};
