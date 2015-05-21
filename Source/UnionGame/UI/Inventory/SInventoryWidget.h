// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MyHUD.h"
#include "Slate.h"

/**
 * 
 */
class UNIONGAME_API SInventoryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInventoryWidget)
	{}

		SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


protected:
	void GetInventory();

	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	int32		c; //Columns
	int32		r; //Rows
	TSharedPtr<class SUniformGridPanel> Container;
};
