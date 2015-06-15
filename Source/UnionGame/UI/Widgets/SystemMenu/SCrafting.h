// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "System/CraftingSystem/CraftingManager.h"
#include "Slate.h"


/**
*
*/
class UNIONGAME_API SCrafting : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCrafting)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	


protected:
	void GetCrafting();
	const FSlateBrush* GetItemImage(int32 index) const;
	FText GetCraftableText(int32 index) const;
	FReply CraftItem(int32 index) const;
	FReply ToggleCrafting() const;
	

	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	int32		c; //Columns
	int32		r; //Rows
	int32		i; //ItemCounter
	TSharedPtr<class SUniformGridPanel> Container;
};
