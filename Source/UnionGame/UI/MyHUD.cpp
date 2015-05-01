// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "MyHUD.h"
#include "SResourceBar.h"
#include "Engine.h"

AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxValue = 2000.0f;
	Value = 1000.0f;
}

void AMyHUD::DrawHUD()
{
	

	DrawHUD_DrawMainInfo();

	Super::DrawHUD();
}

void AMyHUD::DrawHUD_DrawMainInfo()
{
	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(2)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.MaxWidth(1200.0f)
				[
					SNew(SResourceBar)
					.Value(Value)
					.MaxValue(MaxValue)
					.BarColor(FLinearColor::Green)
					.OwnerHUD(this)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(2)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.MaxWidth(900.0f)
				[
					SNew(SResourceBar)
					.Value(Value)
					.MaxValue(MaxValue)
					.BarColor(FLinearColor::Yellow)
					.OwnerHUD(this)
				]
			]		
		);
	}
	Value += 1;
}