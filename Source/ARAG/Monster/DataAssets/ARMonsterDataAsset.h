// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "DataAssets/ARActorDataAssetBase.h"
#include "ARMonsterDataAsset.generated.h"

/* 몬스터 속성 데이터 */
UCLASS(BlueprintType, Blueprintable)
class ARAG_API UARMonsterDataAsset : public UARActorDataAssetBase
{
    GENERATED_BODY()

public:
    // 보스 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    bool bIsBoss = false;
    // 이동 가능 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    bool bIsMovable = true;
    // 공격력
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    float AttackDamage = 10.F;
    // 공격 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    float AttackRange = 200.F;
    // 패트롤 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    float PatrolDistance = 1000.F;
    // 플레이어 감지 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    float DetectDistance = 600.F;
    // 최대 플레이어 감지 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    float MaxDetectDistance = 800.F;
    // 시야각 절반
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    float DetectHalfAngle = 75.F;
    // 초기 위치로부터 최대 추적 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
    float MaxTraceDistance = 2000.F;
};
