// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AbilitySystem/ARCharacterAttributeSet.h"
//
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UARCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHPAttribute())   // HP
    {
        SetHP(FMath::Clamp(GetHP(), 0.F, GetMaxHP()));
    }
    else if (Data.EvaluatedData.Attribute == GetMPAttribute())  // MP
    {
        SetMP(FMath::Clamp(GetMP(), 0.F, GetMaxMP()));
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

void UARCharacterAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARCharacterAttributeSet, MaxHP, OldMaxHP);
}

void UARCharacterAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARCharacterAttributeSet, HP, OldHP);
}

void UARCharacterAttributeSet::OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARCharacterAttributeSet, MaxMP, OldMaxMP);
}

void UARCharacterAttributeSet::OnRep_MP(const FGameplayAttributeData& OldMP)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARCharacterAttributeSet, MP, OldMP);
}

void UARCharacterAttributeSet::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UARCharacterAttributeSet, MaxMovementSpeed, OldMaxMovementSpeed);
}

void UARCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UARCharacterAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UARCharacterAttributeSet, HP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UARCharacterAttributeSet, MaxMP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UARCharacterAttributeSet, MP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UARCharacterAttributeSet, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
}
