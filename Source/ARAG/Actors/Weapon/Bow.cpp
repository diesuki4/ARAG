// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/Bow.h"

#include "ActorComponents/AR_QuiverComponent.h"
#include "Actors/Weapon/Arrow.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABow::ABow()
{

}

void ABow::Equip(AARAGCharacter* NewCharacter)
{
    Super::Equip(NewCharacter);

    USkeletalMeshComponent* CharacterMesh = NewCharacter->GetMesh();
    ARCHECK(CharacterMesh != nullptr);
    // 캐릭터 메시에 화살집 컴포넌트 부착
    if (CharacterMesh->DoesSocketExist(QuiverSocket))
    {
        UActorComponent* ActorComponent = NewCharacter->AddComponentByClass(QuiverComponentClass, true, FTransform(), false);
        ARCHECK(ActorComponent != nullptr);

        QuiverComponent = Cast<UAR_QuiverComponent>(ActorComponent);
        QuiverComponent->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, QuiverSocket);
    }
}

void ABow::Unequip()
{
    USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
    ARCHECK(CharacterMesh != nullptr);
    // 캐릭터 메시에서 화살집 컴포넌트 해제
    if (CharacterMesh->DoesSocketExist(QuiverSocket))
    {
        ARCHECK(QuiverComponent != nullptr);

        QuiverComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
        QuiverComponent->DestroyComponent();
    }

    Super::Unequip();
}
// AttackStart() 호출
void ABow::LfMousePressed()
{
    Super::LfMousePressed();

    ARCHECK(CharacterAnimInstance != nullptr);

    if (CanUse())   // 화살을 다시 집어넣는 중에 쏘는 것을 방지하기 위함
    {
        CharacterAnimInstance->PlayAttackMontage();
        CharacterAnimInstance->JumpToMontageSection(ESectionName::LfMousePressed);
    }
}
// Attack() 호출
void ABow::LfMouseReleased()
{
    Super::LfMouseReleased();

    ARCHECK(CharacterAnimInstance != nullptr);
    ARCHECK(CurrentArrow != nullptr);
    
    // 화살을 다시 집어넣는 중에 쏘는 것을 방지하기 위함
    if (CharacterAnimInstance->GetCurrentSection() == ESectionName::LfMousePressed)
    {
        CharacterAnimInstance->PlayAttackMontage();
        CharacterAnimInstance->JumpToMontageSection(ESectionName::LfMouseReleased);
    }
}
// AttackEnd() 호출
void ABow::RtMousePressed()
{
    Super::RtMousePressed();

    ARCHECK(CharacterAnimInstance != nullptr);
    ARCHECK(CurrentArrow != nullptr);

    CharacterAnimInstance->PlayAttackMontage();
    CharacterAnimInstance->JumpToMontageSection(ESectionName::RtMousePressed);
}

bool ABow::CanUse()
{
    ARCHECK(Super::CanUse(), false);
    ARCHECK(QuiverComponent != nullptr, false);
    // 캐릭터 손에 화살이 없다 && 화살집에 남은 화살이 있다
    return (CurrentArrow == nullptr) && QuiverComponent->CanPick();
}

void ABow::AttackStart()
{
    Super::AttackStart();

    ARCHECK(QuiverComponent != nullptr);
    // 화살집에서 화살을 가져왔으면
    if ((CurrentArrow = QuiverComponent->Pick()) != nullptr)
    {
        // 캐릭터 메시 손 부분에 붙인다.
        USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
        ARCHECK(CharacterMesh != nullptr);

        CurrentArrow->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ArrowSocket);
        // 방향은 시선 방향으로 고정
        Character->bUseControllerRotationYaw = true;
    }
}

void ABow::Attack()
{
    Super::Attack();

    ARCHECK(CurrentArrow != nullptr);

    UProjectileMovementComponent* ProjectileMovement = CurrentArrow->GetProjectileMovement();
    ARCHECK(ProjectileMovement != nullptr);
    // 캐릭터 손에서 화살을 떼고 발사시킨다.
    CurrentArrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    ProjectileMovement->Velocity = CurrentArrow->GetActorForwardVector() * ProjectileMovement->InitialSpeed;
    ProjectileMovement->Activate();

    CurrentArrow = nullptr;
    // 캐릭터 방향 설정 복원
    Character->bUseControllerRotationYaw = false;
}

void ABow::AttackEnd()
{
    ARCHECK(QuiverComponent != nullptr);
    // 손에 화살이 있으면 (화살을 손에 들고 우클릭을 눌렀으면)
    if (CurrentArrow != nullptr)
    {
        // 다시 화살집에 넣는다.
        CurrentArrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        QuiverComponent->Put(CurrentArrow);

        CurrentArrow = nullptr;
    }

    // 캐릭터 방향 설정 복원
    Character->bUseControllerRotationYaw = false;

    Super::AttackEnd();
}
