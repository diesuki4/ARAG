// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARAGGameMode.h"
#include "ARAGCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "AR_PlayerController.h"

AARAGGameMode::AARAGGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	ARCHECK(PlayerPawnBPClass.Class != nullptr);

	DefaultPawnClass = PlayerPawnBPClass.Class;

    PlayerControllerClass = AAR_PlayerController::StaticClass();
}
