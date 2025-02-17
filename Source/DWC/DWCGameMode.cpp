// Copyright Epic Games, Inc. All Rights Reserved.

#include "DWCGameMode.h"
#include "DWCCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADWCGameMode::ADWCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
