// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "SImageButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SImageButton::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;

	ChildSlot
		[
			SNew(SButton)
			.OnClicked(InArgs._OnClicked)
			.ButtonColorAndOpacity(FColor(0,0,0,1))
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.Padding(2)
				[
					SNew(SImage)
					.Image(InArgs._Image)
				]
				+ SOverlay::Slot()
					.VAlign(InArgs._TextVAlign)
					.HAlign(InArgs._TextHAlign)
					.Padding(10)
					[
						SNew(STextBlock)
						.Font(InArgs._Font)
						.Text(InArgs._Text)
						.ColorAndOpacity(FColor::White)
					]	
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
