// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "SResourceBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SResourceBar::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	MaxValue = InArgs._MaxValue;
	Value = InArgs._Value;
	Color = InArgs._BarColor;

	float Persentage = (GetValue() / GetMaxValue());


	ChildSlot
	[
		//SNew(SScrollBox)
		//+ SScrollBox::Slot().Padding(10, 5)
		//[
		//	SNew(SHorizontalBox)
		//	+ SHorizontalBox::Slot()
		//	[
				SNew(SProgressBar)
				.FillColorAndOpacity(Color.Get())
				.Percent(Persentage)
		//	]
		//]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
