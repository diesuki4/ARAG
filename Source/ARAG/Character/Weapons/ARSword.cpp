// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Weapons/ARSword.h"

AARSword::AARSword()
{

}

void AARSword::LfMousePressed()
{
    Super::LfMousePressed();
    // Attack 애님 노티파이를 통해 Attack() 함수를 호출한다.
    ARCHECK(CharacterAnimInstance != nullptr);

    // 검을 사용할 수 있으면
    if (CanUse())
    {
        // 공격 몽타주 재생
        CharacterAnimInstance->PlayAttackMontage();
        CharacterAnimInstance->JumpToMontageSection(EARCharacterMontageSectionName::LfMousePressed_ML);
    }
}

void AARSword::Attack()
{
    Super::Attack();

    MeleeAttack();
}
