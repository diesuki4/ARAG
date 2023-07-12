// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

/* Input Mapping Context 설정 시 우선순위 열거형 */
UENUM(BlueprintType)
enum class EARInputMappingPriority : uint8
{
    Movement  UMETA(DisplayName = "Movement"),
    Weapon    UMETA(DisplayName = "Weapon"),

    MAX       UMETA(DisplayName = "Default MAX")
};
