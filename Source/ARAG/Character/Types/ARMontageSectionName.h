// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

/* 애니메이션 몽타주 상의 섹션 이름을 매핑하기 위한 열거형 */
UENUM(BlueprintType)
enum class EARMontageSectionName : uint8
{
    LfMousePressed   UMETA(DisplayName = "LfMousePressed"),
    LfMouseReleased  UMETA(DisplayName = "LfMouseReleased"),
    RtMousePressed   UMETA(DisplayName = "RtMousePressed"),

    MAX    UMETA(DisplayName = "Default MAX")
};
