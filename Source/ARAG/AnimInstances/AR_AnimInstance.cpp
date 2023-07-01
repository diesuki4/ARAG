// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/AR_AnimInstance.h"

#include "Animation/AnimMontage.h"
#include "ARAGCharacter.h"
#include "ActorComponents/AR_CombatComponent.h"

UAR_AnimInstance::UAR_AnimInstance()
{

}

void UAR_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

}

void UAR_AnimInstance::SetAttackMontage(UAnimMontage* NewAttackMontage)
{
    AttackMontage = NewAttackMontage;
}

void UAR_AnimInstance::PlayAttackMontage()
{
    if (!Montage_IsPlaying(AttackMontage))
    {
        Montage_Play(AttackMontage);
    }
}

ESectionName UAR_AnimInstance::GetCurrentSection()
{
    return CurrentSection;
}

void UAR_AnimInstance::JumpToMontageSection(ESectionName NewSection)
{
    CurrentSection = NewSection;

    Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

FName UAR_AnimInstance::GetAttackMontageSectionName(ESectionName NewSection)
{
    switch (NewSection)
    {
        case ESectionName::LfMousePressed:  return LfMousePressedSectionName;
        case ESectionName::LfMouseReleased: return LfMouseReleasedSectionName;
        case ESectionName::RtMousePressed:  return RtMousePressedSectionName;
        default:                            return TEXT("");
    }
}

void UAR_AnimInstance::AnimNotify_AttackStart()
{
    OnAttackStart.Broadcast();
}

void UAR_AnimInstance::AnimNotify_Attack()
{
    OnAttack.Broadcast();
}

void UAR_AnimInstance::AnimNotify_AttackEnd()
{
    OnAttackEnd.Broadcast();
}
