// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ARActorData.generated.h"

/* 액터 데이터 */
USTRUCT(BlueprintType)
struct FARActorData
{
    GENERATED_USTRUCT_BODY()
    
    // 기본 액터 적용 이펙트
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
    TArray<TSubclassOf<class UGameplayEffect>> Effects;

    // 기본 액터 부여 능력
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
    TArray<TSubclassOf<class UGameplayAbility>> Abilities;
};
