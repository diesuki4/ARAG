// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "AbilitySystemComponent.h"
#include "ARAbilitySystemComponent.generated.h"

class UGameplayEffect;
class UGameplayAbility;

/* GAS 컴포넌트 */
UCLASS()
class ARAG_API UARAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
    UARAbilitySystemComponent();

    // 능력 부여 래퍼 함수
    void GiveAbility(TSubclassOf<UGameplayAbility> Ability);
    void GiveAbility(TArray<TSubclassOf<UGameplayAbility>> Abilities);
    // 이펙트 적용 래퍼 함수
    bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);
    bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, UObject* NewSourceObject = nullptr);
    bool ApplyGameplayEffectToSelf(TArray<TSubclassOf<UGameplayEffect>> Effects, UObject* NewSourceObject = nullptr);
};
