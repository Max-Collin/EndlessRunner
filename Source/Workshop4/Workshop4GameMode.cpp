// Copyright Epic Games, Inc. All Rights Reserved.

#include "Workshop4GameMode.h"
#include "Workshop4Character.h"
#include "UObject/ConstructorHelpers.h"

AWorkshop4GameMode::AWorkshop4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
