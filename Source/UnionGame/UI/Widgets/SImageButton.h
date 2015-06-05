// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Slate.h"

/**
 * 
 */
class UNIONGAME_API SImageButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SImageButton)
	{ }
		// The label to display on the button.
		SLATE_ATTRIBUTE(FText, Text)

		// The label to display on the button.
		SLATE_ATTRIBUTE(const FSlateBrush*, Image)

		SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

		// Called when the button is clicked.
		SLATE_EVENT(FOnClicked, OnClicked)
		SLATE_END_ARGS()

		// Construct this button
		void Construct(const FArguments& InArgs);

protected:
	TWeakObjectPtr<class AMyHUD> OwnerHUD;
	FText Amount;
};
