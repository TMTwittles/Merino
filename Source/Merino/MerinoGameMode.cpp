// Copyright Epic Games, Inc. All Rights Reserved.

#include "MerinoGameMode.h"
#include "MerinoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMerinoGameMode::AMerinoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
