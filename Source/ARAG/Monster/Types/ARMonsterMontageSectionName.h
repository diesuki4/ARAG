// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

/* 몬스터 애니메이션 몽타주 상의 섹션 이름을 매핑하기 위한 열거형 */
UENUM(BlueprintType)
enum class EARMonsterMontageSectionName : uint8
{
    AttackSection   UMETA(DisplayName = "AttackSection"),

    MAX             UMETA(DisplayName = "Default MAX")
};
