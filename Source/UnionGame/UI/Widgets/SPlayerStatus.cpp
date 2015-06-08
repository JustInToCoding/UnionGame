// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "SPlayerStatus.h"
#include "MyGameResources.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPlayerStatus::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	HealthMaxValue = InArgs._HealthMaxValue;
	HealthValue = InArgs._HealthValue;
	StaminaMaxValue = InArgs._StaminaMaxValue;
	StaminaValue = InArgs._StaminaValue;
	
	const FSlateBrush* HUDBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.HUD")));
	const FSlateBrush* HealthBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.Health")));
	const FSlateBrush* StaminaBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.Stamina")));
	const FSlateBrush* TransparentBrush = FMyUIResources::GetSlateStyleResources().GetBrush(FName(*FString("UnionGame.Transparent")));

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Bottom)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			[
				SNew(SBox)
				.HeightOverride(204.0f)
				.WidthOverride(140.0f)
				[
					SNew(SProgressBar)
					.Percent(this, &SPlayerStatus::getHealthPercentage)		
					.FillImage(HealthBrush)
					.BackgroundImage(TransparentBrush)
					.BarFillType(EProgressBarFillType::BottomToTop)
				]
			]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Bottom)
				[
					SNew(SBox)
					.HeightOverride(204.0f)
					.WidthOverride(140.0f)
					[
						SNew(SProgressBar)
						.Percent(this, &SPlayerStatus::getStaminaPercentage)
						.FillImage(StaminaBrush)
						.BackgroundImage(TransparentBrush)
						.BarFillType(EProgressBarFillType::BottomToTop)
					]
				]
		]
		+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SImage)
					.Image(HUDBrush)
				]
			]
	];
}

TOptional<float> SPlayerStatus::getHealthPercentage() const{
	return OwnerHUD->healthPercentage;
}

TOptional<float> SPlayerStatus::getStaminaPercentage() const{
	return OwnerHUD->staminaPercentage;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION