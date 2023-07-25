// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AbilitySystem/ARMonsterAttributeSet.h"
//
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UARMonsterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHPAttribute())   // HP
    {
        SetHP(FMath::Clamp(GetHP(), 0.F, GetMaxHP()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxMovementSpeedAttribute())    // MaxMovementSpeed
    {
        ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());
        ARCHECK(OwningCharacter != nullptr);

        UCharacterMovementComponent* CharacterMovement = OwningCharacter->GetCharacterMovement();
        ARCHECK(CharacterMovement != nullptr);

        CharacterMovement->MaxWalkSpeed = GetMaxMovementSpeed();
    }
}

void UARMonsterAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARMonsterAttributeSet, MaxHP, OldMaxHP);
}

void UARMonsterAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARMonsterAttributeSet, HP, OldHP);
}

void UARMonsterAttributeSet::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARMonsterAttributeSet, MaxMovementSpeed, OldMaxMovementSpeed);
}

void UARMonsterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UARMonsterAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UARMonsterAttributeSet, HP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UARMonsterAttributeSet, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
}
