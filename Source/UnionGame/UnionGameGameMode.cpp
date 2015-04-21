// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnionGame.h"
#include "UnionGameGameMode.h"
#include "UnionGameCharacter.h"

<<<<<<< HEAD
AUnionGameGameMode::AUnionGameGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
=======

//test: Testing for myself

>>>>>>> 61e4b8e8d5a3a802a4443fc2785081012c041ce0
