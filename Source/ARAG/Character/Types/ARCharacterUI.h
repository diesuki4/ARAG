// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

/* HUD UI의 위젯들을 나타내는 열거형 */
UENUM(BlueprintType)
enum class EARCharacterUI : uint8
{
    Crosshair   UMETA(DisplayName = "Crosshair"),

    MAX         UMETA(DisplayName = "Default MAX")
};
