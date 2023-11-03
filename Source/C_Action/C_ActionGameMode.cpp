// Copyright Epic Games, Inc. All Rights Reserved.

#include "C_ActionGameMode.h"
#include "C_ActionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AC_ActionGameMode::AC_ActionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
