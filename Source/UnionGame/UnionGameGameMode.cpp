// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnionGame.h"
#include "UnionGameGameMode.h"
#include "UnionGameCharacter.h"

AUnionGameGameMode::AUnionGameGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
