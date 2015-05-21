// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyHUD.h"
#include "Slate.h"

/**
 * 
 */
class UNIONGAME_API SResourceBar : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SResourceBar)
	{}

		SLATE_ATTRIBUTE(float, Value)

		SLATE_ATTRIBUTE(float, MaxValue)

		SLATE_ATTRIBUTE(FLinearColor, BarColor)

		SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	float GetValue() const
	{
		if (Value.IsSet())
		{
			return Value.Get();
		}

		return 0.0f;
	}

	float GetMaxValue() const
	{
		if (MaxValue.IsSet())
		{
			return MaxValue.Get();
		}

		return 0.0f;
	}

protected:
	TWeakObjectPtr<class AMyHUD> OwnerHUD;
	TAttribute<float> MaxValue;
	TAttribute<float> Value;
	TAttribute<FLinearColor> Color;
};
