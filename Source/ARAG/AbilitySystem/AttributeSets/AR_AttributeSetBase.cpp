// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/AR_AttributeSetBase.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAR_AttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }
    else if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
        SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxMovementSpeedAttribute())
    {
        ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());
        ARCHECK(OwningCharacter != nullptr);

        UCharacterMovementComponent* CharacterMovement = OwningCharacter->GetCharacterMovement();
        ARCHECK(CharacterMovement != nullptr);

        CharacterMovement->MaxWalkSpeed = GetMaxMovementSpeed();
    }
}

void UAR_AttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAR_AttributeSetBase, MaxHealth, OldMaxHealth);
}

void UAR_AttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAR_AttributeSetBase, Health, OldHealth);
}

void UAR_AttributeSetBase::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAR_AttributeSetBase, MaxMana, OldMaxMana);
}

void UAR_AttributeSetBase::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAR_AttributeSetBase, Mana, OldMana);
}

void UAR_AttributeSetBase::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAR_AttributeSetBase, MaxMovementSpeed, OldMaxMovementSpeed);
}

void UAR_AttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UAR_AttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAR_AttributeSetBase, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAR_AttributeSetBase, MaxMana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAR_AttributeSetBase, Mana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAR_AttributeSetBase, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
}
