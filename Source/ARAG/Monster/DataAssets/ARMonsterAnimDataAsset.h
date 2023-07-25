// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "DataAssets/ARActorAnimDataAssetBase.h"
#include "ARMonsterAnimDataAsset.generated.h"

/* 몬스터 에니메이션 데이터 */
UCLASS(BlueprintType, Blueprintable)
class ARAG_API UARMonsterAnimDataAsset : public UARActorAnimDataAssetBase
{
    GENERATED_BODY()

public:
    // 기본 이동
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UBlendSpace* MovementBlendspace = nullptr;
    // 피격
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UAnimSequenceBase* DamagedAnim = nullptr;
    // 죽음
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UAnimSequenceBase* DieAnim = nullptr;
    // 공격
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UAnimMontage* AttackMontage = nullptr;
};
