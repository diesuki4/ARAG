// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CharacterData.generated.h"

/* 캐릭터 데이터 */
USTRUCT(BlueprintType)
struct FCharacterData
{
    GENERATED_USTRUCT_BODY()
    
    // 기본 캐릭터 적용 이펙트
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
    TArray<TSubclassOf<class UGameplayEffect>> Effects;

    // 기본 캐릭터 부여 능력
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
    TArray<TSubclassOf<class UGameplayAbility>> Abilities;
};
