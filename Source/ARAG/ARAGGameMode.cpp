// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARAGGameMode.h"
#include "ARAGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AARAGGameMode::AARAGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	ARCHECK(PlayerPawnBPClass.Class != nullptr);

	DefaultPawnClass = PlayerPawnBPClass.Class;

}
