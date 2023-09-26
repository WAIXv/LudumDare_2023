// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ludum_2023GameMode.h"
#include "Ludum_2023Character.h"
#include "UObject/ConstructorHelpers.h"

ALudum_2023GameMode::ALudum_2023GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
