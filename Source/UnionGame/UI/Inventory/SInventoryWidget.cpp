// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "SInventoryWidget.h"

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
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SInventoryWidget::GetInventory()
{
	Container = SNew(SUniformGridPanel).SlotPadding(FMargin(5.0f));

	for (int c = 0; c < 3; c++)
	{
		for (int r = 0; r < 5; r++)
		{
			Container->AddSlot(c, r)
				[
					SNew(SBox)
					.WidthOverride(128.f)
					.HeightOverride(128.f)
					[
						SNew(SImage)
					]
				];
		}
	}
}