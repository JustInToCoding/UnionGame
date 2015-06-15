// Fill out your copyright notice in the Description page of Project Settings.


#include "UnionGame.h"
#include "SCrafting.h"
#include "../SImageButton.h"
#include "MyGameResources.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCrafting::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;

	const FSlateBrush* MenuBackgroundBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.MenuBackground")));
	const FSlateBrush* MenuButtonBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.MenuButton")));

	GetCrafting();

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
								.OnClicked(this, &SCrafting::ToggleCrafting)
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

void SCrafting::GetCrafting()
{
	Container = SNew(SUniformGridPanel).SlotPadding(FMargin(5.0f));

	for (int32 r = 0; r < 3; r++)
	{
		for (int32 c = 0; c < 3; c++)
		{
			Container->AddSlot(c, r)
				[
					SNew(SBox)
					.WidthOverride(128.f)
					.HeightOverride(128.f)
					[
						SNew(SImageButton)
						.Image(this, &SCrafting::GetItemImage, c + r * 3)
						.Text(this, &SCrafting::GetCraftableText, c + r * 3)
						.Font(FSlateFontInfo("Veranda", 12))
						.OnClicked(this, &SCrafting::CraftItem, c + r * 3)
						.TextVAlign(VAlign_Bottom)
						.TextHAlign(HAlign_Right)
					]
				];
		}
	}
}

const FSlateBrush* SCrafting::GetItemImage(int32 index) const
{
	const FSlateBrush* Brush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.Transparent")));
	TArray<FString> Craftables = UCraftingManager::getInstance()->getAllCraftable();

	if (Craftables.IsValidIndex(index))
	{
		FString CraftID = Craftables[index];
		FName Name = FName(*FString("UnionGame." + CraftID));
		Brush = FMyUIResources::GetSlateStyleResources().GetBrush(Name);
	}
	return Brush;
}

FText SCrafting::GetCraftableText(int32 index) const
{
	FText canCraft;
	TArray<FString> Craftables = UCraftingManager::getInstance()->getAllCraftable();
	if (Craftables.IsValidIndex(index))
	{
		FString CraftID = Craftables[index];
		canCraft = FText::FromString(FString::FromInt(UCraftingManager::getInstance()->canCraft(CraftID)));
	}

	return canCraft;
}

FReply SCrafting::CraftItem(int32 index) const
{
	TArray<FString> Craftables = UCraftingManager::getInstance()->getAllCraftable();
	if (Craftables.IsValidIndex(index))
	{
		FString CraftID = Craftables[index];
		UCraftingManager::getInstance()->craftItem(CraftID);
	}
	
	return FReply::Handled();
}

FReply SCrafting::ToggleCrafting() const
{
	OwnerHUD->ShowCrafting = !OwnerHUD->ShowCrafting;

	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION