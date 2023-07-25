// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
/*
    애니메이션 몽타주 상의 섹션 이름을 매핑하기 위한 열거형
    (ML = Melee 근접 공격)
*/
UENUM(BlueprintType)
enum class EARCharacterMontageSectionName : uint8
{
    LfMousePressed      UMETA(DisplayName = "LfMousePressed"),
    LfMousePressed_ML   UMETA(DisplayName = "LfMousePressed_ML"),

    LfMouseReleased     UMETA(DisplayName = "LfMouseReleased"),
    LfMouseReleased_ML  UMETA(DisplayName = "LfMouseReleased_ML"),

    RtMousePressed      UMETA(DisplayName = "RtMousePressed"),
    RtMousePressed_ML   UMETA(DisplayName = "RtMousePressed_ML"),

    MAX                 UMETA(DisplayName = "Default MAX")
};
