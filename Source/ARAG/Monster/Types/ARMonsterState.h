// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

/* 몬스터의 상태를 나타내기 위한 열거형 */
UENUM(BlueprintType)
enum class EARMonsterState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Patrol      UMETA(DisplayName = "Patrol"),
    Chase       UMETA(DisplayName = "Chase"),
    Attack      UMETA(DisplayName = "Attack"),
    Return      UMETA(DisplayName = "Return"),
    Damaged     UMETA(DisplayName = "Damaged"),
    Die         UMETA(DisplayName = "Die"),

    MAX         UMETA(DisplayName = "Default MAX")
};
