// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ARAbilitySystemComponent.h"
//
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

UARAbilitySystemComponent::UARAbilitySystemComponent()
{
    SetIsReplicated(true);
    SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void UARAbilitySystemComponent::GiveAbility(TSubclassOf<UGameplayAbility> Ability)
{
    ARCHECK(IsOwnerActorAuthoritative());
    
    Super::GiveAbility(FGameplayAbilitySpec(Ability));
}

void UARAbilitySystemComponent::GiveAbility(TArray<TSubclassOf<UGameplayAbility>> Abilities)
{
    ARCHECK(IsOwnerActorAuthoritative());

    for (auto Ability : Abilities)
    {
        GiveAbility(Ability);
    }
}

bool UARAbilitySystemComponent::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext)
{
    ARCHECK(GetOwner()->GetLocalRole() == ROLE_Authority, false);
    ARCHECK(Effect.Get(), false);

    FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(Effect, 1, InEffectContext);
    ARCHECK(SpecHandle.IsValid(), false);

    FActiveGameplayEffectHandle ActiveGEHandle = Super::ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

    return ActiveGEHandle.WasSuccessfullyApplied();
}

bool UARAbilitySystemComponent::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, UObject* NewSourceObject)
{
    ARCHECK(GetOwner()->GetLocalRole() == ROLE_Authority, false);
    ARCHECK(Effect.Get(), false);

    NewSourceObject = (NewSourceObject == nullptr) ? this : NewSourceObject;

    FGameplayEffectContextHandle EffectContext = MakeEffectContext();
    EffectContext.AddSourceObject(NewSourceObject);

    return ApplyGameplayEffectToSelf(Effect, EffectContext);
}

bool UARAbilitySystemComponent::ApplyGameplayEffectToSelf(TArray<TSubclassOf<UGameplayEffect>> Effects, UObject* NewSourceObject)
{
    ARCHECK(GetOwner()->GetLocalRole() == ROLE_Authority, false);
    for (auto Effect : Effects) ARCHECK(Effect.Get(), false);

    NewSourceObject = (NewSourceObject == nullptr) ? this : NewSourceObject;

    FGameplayEffectContextHandle EffectContext = MakeEffectContext();
    EffectContext.AddSourceObject(NewSourceObject);

    bool bResult = true;

    for (auto Effect : Effects)
    {
        bResult &= ApplyGameplayEffectToSelf(Effect, EffectContext);
    }

    return bResult;
}
