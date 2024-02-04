// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_ProjectGameMode.h"
#include "TPS_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPS_ProjectGameMode::ATPS_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
