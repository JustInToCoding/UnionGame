// Fill out your copyright notice in the Description page of Project Settings.


#include "UnionGame.h"
#include "SInventoryWidget.h"
#include "../SImageButton.h"
#include "MyGameResources.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInventoryWidget::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;

	GetInventory();

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(100)
		[
			SNew(SBorder)
			.ColorAndOpacity(FColor::White)
			[
			
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoHeight()
			[
				SNew(STextBlock)
				.Font(FSlateFontInfo("Veranda", 32))
				.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
				.Text(FText::FromString("Inventory"))
			]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				[
					Container.ToSharedRef()
				]
			]
		]
	];
}

void SInventoryWidget::GetInventory()
{
	Container = SNew(SUniformGridPanel).SlotPadding(FMargin(5.0f));
	TArray<FEntry> Inventory = UInventory::getInstance()->GetCurrentInventory();
	int32 i = 0;

	for (int32 r = 0; r <= 2; r++)
	{
		for (int32 c = 0; c <= 4; c++)
		{
			if (Inventory.IsValidIndex(i))
			{
				const FSlateBrush* Brush = GetItemImage(i);
				Container->AddSlot(c, r)
					[
						SNew(SBox)
						.WidthOverride(128.f)
						.HeightOverride(128.f)
						[
							SNew(SImageButton)
							.Image(Brush)
							.Text(this, &SInventoryWidget::GetItemText, i)
						]
					];
			}
			else
			{
				Container->AddSlot(c, r)
					[
						SNew(SBox)
						.WidthOverride(128.f)
						.HeightOverride(128.f)
						[
							SNew(SImageButton)
						]
					];
			}
			i++;
		}
	}
}

FText SInventoryWidget::GetItemText(int32 index) const
{
	TArray<FEntry> Inventory = UInventory::getInstance()->GetCurrentInventory();

	FText Amount = FText::FromString(FString::FromInt(Inventory[index].amount));

	return Amount;
}

const FSlateBrush* SInventoryWidget::GetItemImage(int32 index)
{
	TArray<FEntry> Inventory = UInventory::getInstance()->GetCurrentInventory();
	FName Name = FName(*FString("UnionGame." + Inventory[index].id));
	const FSlateBrush* Brush = FMyUIResources::GetSlateStyleResources().GetBrush(Name);

	return Brush;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION