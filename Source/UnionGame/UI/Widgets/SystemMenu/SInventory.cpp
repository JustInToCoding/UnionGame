// Fill out your copyright notice in the Description page of Project Settings.


#include "UnionGame.h"
#include "SInventory.h"
#include "../SImageButton.h"
#include "MyGameResources.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInventory::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;

	const FSlateBrush* MenuBackgroundBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.MenuBackground")));
	const FSlateBrush* MenuButtonBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.MenuButton")));

	GetInventory();

	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			[

				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SImage)
					.Image(MenuBackgroundBrush)
				]
			]
			+ SOverlay::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(100)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Center)
						[
							SNew(SBox)
							.WidthOverride(160.f)
							.HeightOverride(60.f)
							.HAlign(HAlign_Center)
							[
								SNew(SImageButton)
								.Image(MenuButtonBrush)
								.Text(FText::FromString("Item"))
								.Font(FSlateFontInfo("Veranda", 16))
								.TextHAlign(HAlign_Center)
							]
						]
						+ SHorizontalBox::Slot()
							.HAlign(HAlign_Center)
							[
								SNew(SBox)
								.WidthOverride(160.f)
								.HeightOverride(60.f)
								.HAlign(HAlign_Center)
								[
									SNew(SImageButton)
									.Image(MenuButtonBrush)
									.Text(FText::FromString("Crafting"))
									.Font(FSlateFontInfo("Veranda", 16))
									.OnClicked(this, &SInventory::ToggleCrafting)
									.TextHAlign(HAlign_Center)
								]
							]
					]
					+ SVerticalBox::Slot()
						.VAlign(VAlign_Top)
						.AutoHeight()
						.Padding(100)
						[
							Container.ToSharedRef()
						]
				]
		];
}

void SInventory::GetInventory()
{
	Container = SNew(SUniformGridPanel).SlotPadding(FMargin(5.0f));
	TArray<FEntry> Inventory = UInventory::getInstance()->GetCurrentInventory();

	for (int32 r = 0; r < 3; r++)
	{
		for (int32 c = 0; c < 3; c++)
		{
				Container->AddSlot(c, r)
					[
						SNew(SBox)
						.WidthOverride(128.0f)
						.HeightOverride(128.0f)
						[
							SNew(SImageButton)
							.Image(this, &SInventory::GetItemImage, c + r * 3)
							.Text(this, &SInventory::GetItemText, c + r * 3)
							.Font(FSlateFontInfo("Veranda", 12))
							.TextVAlign(VAlign_Bottom)
							.TextHAlign(HAlign_Right)
						]
					];
		}
	}
}

FText SInventory::GetItemText(int32 index) const
{
	FText Amount;
	TArray<FEntry> Inventory = UInventory::getInstance()->GetCurrentInventory();
	if (Inventory.IsValidIndex(index))
	{
		Amount = FText::FromString(FString::FromInt(Inventory[index].amount));
	}

	return Amount;
}

const FSlateBrush* SInventory::GetItemImage(int32 index) const
{
	const FSlateBrush* Brush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.Transparent")));
	TArray<FEntry> Inventory = UInventory::getInstance()->GetCurrentInventory();
	if (Inventory.IsValidIndex(index))
	{
		FName Name = FName(*FString("UnionGame." + Inventory[index].id));
		Brush = FMyUIResources::GetSlateStyleResources().GetBrush(Name);
	}
	return Brush;
}

FReply SInventory::ToggleCrafting() const
{
	OwnerHUD->ShowCrafting = !OwnerHUD->ShowCrafting;

	return FReply::Handled();
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION