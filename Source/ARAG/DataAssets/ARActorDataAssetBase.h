// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Engine/DataAsset.h"
#include "ARActorDataAssetBase.generated.h"
/*
    액터 속성 데이터
    (캐릭터와 몬스터 = 액터로 칭함)
*/
UCLASS(BlueprintType, Blueprintable)
class ARAG_API UARActorDataAssetBase : public UDataAsset
{
    GENERATED_BODY()
 
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
    float MaxHP = 30.F;

    // 기본 액터 적용 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
    TArray<TSubclassOf<class UGameplayEffect>> Effects;

    // 기본 액터 부여 능력
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
    TArray<TSubclassOf<class UGameplayAbility>> Abilities;

    // 액터 애니메이션 데이터
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    class UARActorAnimDataAssetBase* AnimDataAsset = nullptr;
};
