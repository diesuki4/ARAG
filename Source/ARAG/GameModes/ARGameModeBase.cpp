// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/ARGameModeBase.h"
//
#include "UObject/ConstructorHelpers.h"
#include "Character/ARCharacter.h"
#include "Character/ARPlayerController.h"

AARGameModeBase::AARGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> CharacterBP(TEXT("Blueprint'/Game/Character/BP_Character.BP_Character_C'"));
	ARCHECK(CharacterBP.Class != nullptr);
	DefaultPawnClass = CharacterBP.Class;

    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBP(TEXT("Blueprint'/Game/Character/BP_PlayerController.BP_PlayerController_C'"));
    ARCHECK(PlayerControllerBP.Class != nullptr);
    PlayerControllerClass = PlayerControllerBP.Class;
}
