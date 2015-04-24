// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"

AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Use the RobotoDistanceField font from the engine
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;
}

void AMyHUD::DrawHUD()
{
	//Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	//Call to the parent versions of DrawHUD
	Super::DrawHUD();

	//Get the Character and Draw message
	ACharacter* MyCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	DrawText("TestTextABC", FColor::White, 50, 50, HUDFont);
}

