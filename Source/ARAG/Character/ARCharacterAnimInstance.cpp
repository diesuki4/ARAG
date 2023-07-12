// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ARCharacterAnimInstance.h"
//
#include "Animation/AnimMontage.h"

UARCharacterAnimInstance::UARCharacterAnimInstance()
{

}

void UARCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

}

void UARCharacterAnimInstance::SetAttackMontage(UAnimMontage* NewAttackMontage)
{
    AttackMontage = NewAttackMontage;
}

void UARCharacterAnimInstance::PlayAttackMontage()
{
    if (!Montage_IsPlaying(AttackMontage))
    {
        Montage_Play(AttackMontage);
    }
}

EARMontageSectionName UARCharacterAnimInstance::GetCurrentSection()
{
    return CurrentSection;
}

void UARCharacterAnimInstance::JumpToMontageSection(EARMontageSectionName NewSection)
{
    CurrentSection = NewSection;

    Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

FName UARCharacterAnimInstance::GetAttackMontageSectionName(EARMontageSectionName NewSection)
{
    switch (NewSection)
    {
        case EARMontageSectionName::LfMousePressed:  return LfMousePressedSectionName;
        case EARMontageSectionName::LfMouseReleased: return LfMouseReleasedSectionName;
        case EARMontageSectionName::RtMousePressed:  return RtMousePressedSectionName;
        default:                                     return TEXT("");
    }
}

void UARCharacterAnimInstance::AnimNotify_AttackStart()
{
    OnAttackStart.Broadcast();
}

void UARCharacterAnimInstance::AnimNotify_Attack()
{
    OnAttack.Broadcast();
}

void UARCharacterAnimInstance::AnimNotify_AttackEnd()
{
    OnAttackEnd.Broadcast();
}
