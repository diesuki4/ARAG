// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/ARMonsterAnimInstance.h"
//
#include "Animation/AnimMontage.h"
#include "Monster/ARMonsterBase.h"
#include "Monster/DataAssets/ARMonsterDataAsset.h"
#include "Monster/DataAssets/ARMonsterAnimDataAsset.h"
#include "ActorComponents/ARDataComponent.h"

UARMonsterAnimInstance::UARMonsterAnimInstance()
{
    CurrentSpeed = 0.F;
    MonsterState = EARMonsterState::Idle;
}

void UARMonsterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Monster = Cast<AARMonsterBase>(GetOwningActor());
    ARCHECK(Monster != nullptr);
    // 상태를 받아오기 위해 람다 함수 등록
    Monster->OnStateChanged.AddLambda([this](EARMonsterState OldMonsterState, EARMonsterState NewMonsterState) { MonsterState = NewMonsterState; });
}

void UARMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    ARCHECK(Monster != nullptr);

    CurrentSpeed = Monster->GetVelocity().Size();
}

void UARMonsterAnimInstance::PlayAttackMontage()
{
    if (!Montage_IsPlaying(GetAttackMontage()))
    {
        Montage_Play(GetAttackMontage());
    }
}

EARMonsterMontageSectionName UARMonsterAnimInstance::GetCurrentSection()
{
    return CurrentSection;
}

void UARMonsterAnimInstance::JumpToMontageSection(EARMonsterMontageSectionName NewSection)
{
    CurrentSection = NewSection;

    Montage_JumpToSection(GetAttackMontageSectionName(NewSection), GetAttackMontage());
}

FName UARMonsterAnimInstance::GetAttackMontageSectionName(EARMonsterMontageSectionName NewSection)
{
    switch (NewSection)
    {
        case EARMonsterMontageSectionName::AttackSection:   return AttackSectionName;
        default:                                            return TEXT("");
    }
}

UBlendSpace* UARMonsterAnimInstance::GetMovementBlendspace() const
{
    ARCHECK(Monster != nullptr, nullptr);

    UARDataComponent* DataComponent = Monster->GetDataComponent();
    ARCHECK(DataComponent != nullptr, nullptr);
    // ARMonsterBase의 Data Component를 통해 가져온다.
    UARMonsterDataAsset* MonsterData = Cast<UARMonsterDataAsset>(DataComponent->GetActorData());
    ARCHECK(MonsterData != nullptr, nullptr);

    if (MonsterData->AnimDataAsset)
    {
        UARMonsterAnimDataAsset* MonsterAnimData = Cast<UARMonsterAnimDataAsset>(MonsterData->AnimDataAsset);
        ARCHECK(MonsterAnimData != nullptr, nullptr);

        return MonsterAnimData->MovementBlendspace;
    }

    return nullptr;
}

UAnimMontage* UARMonsterAnimInstance::GetAttackMontage() const
{
    ARCHECK(Monster != nullptr, nullptr);

    UARDataComponent* DataComponent = Monster->GetDataComponent();
    ARCHECK(DataComponent != nullptr, nullptr);
    // ARMonsterBase의 Data Component를 통해 가져온다.
    UARMonsterDataAsset* MonsterData = Cast<UARMonsterDataAsset>(DataComponent->GetActorData());
    ARCHECK(MonsterData != nullptr, nullptr);

    if (MonsterData->AnimDataAsset)
    {
        UARMonsterAnimDataAsset* MonsterAnimData = Cast<UARMonsterAnimDataAsset>(MonsterData->AnimDataAsset);
        ARCHECK(MonsterAnimData != nullptr, nullptr);

        return MonsterAnimData->AttackMontage;
    }

    return nullptr;
}

UAnimSequenceBase* UARMonsterAnimInstance::GetAnimByState(EARMonsterState State) const
{
    ARCHECK(Monster != nullptr, nullptr);

    UARDataComponent* DataComponent = Monster->GetDataComponent();
    ARCHECK(DataComponent != nullptr, nullptr);
    // ARMonsterBase의 Data Component를 통해 가져온다.
    UARMonsterDataAsset* MonsterData = Cast<UARMonsterDataAsset>(DataComponent->GetActorData());
    ARCHECK(MonsterData != nullptr, nullptr);

    if (MonsterData->AnimDataAsset)
    {
        UARMonsterAnimDataAsset* MonsterAnimData = Cast<UARMonsterAnimDataAsset>(MonsterData->AnimDataAsset);
        ARCHECK(MonsterAnimData != nullptr, nullptr);

        switch (State)
        {
        case EARMonsterState::Damaged: return MonsterAnimData->DamagedAnim;
        case EARMonsterState::Die:     return MonsterAnimData->DieAnim;
        }
    }

    return nullptr;
}
