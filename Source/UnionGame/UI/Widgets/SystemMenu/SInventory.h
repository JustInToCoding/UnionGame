// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "System/InventorySystem/Inventory.h"
#include "Slate.h"


/**
*
*/
class UNIONGAME_API SInventory : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInventory)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	


protected:
	void GetInventory();
	FText GetItemText(int32 index) const;
	const FSlateBrush* GetItemImage(int32 index) const;
	FReply ToggleCrafting() const;

	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	int32		c; //Columns
	int32		r; //Rows
	int32		i; //ItemCounter
	TSharedPtr<class SUniformGridPanel> Container;
};
