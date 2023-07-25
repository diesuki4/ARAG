// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

/* 캐릭터의 상태를 나타내기 위한 열거형 */
UENUM(BlueprintType)
enum class EARCharacterState : uint8
{
    Normal      UMETA(DisplayName = "Normal"),
    Attack      UMETA(DisplayName = "Attack"),
    Damaged     UMETA(DisplayName = "Damaged"),
    Die         UMETA(DisplayName = "Die"),

    MAX         UMETA(DisplayName = "Default MAX")
};
