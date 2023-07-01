// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponBase.h"

#include "AR_PlayerController.h"
#include "ARAGTypes/InputMappingPriority.h"
#include "ActorComponents/AR_CombatComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::Equip(AARAGCharacter* NewCharacter)
{
    ARCHECK(NewCharacter != nullptr);
    // 소유자 설정
    SetOwner(Character = NewCharacter);

    CharacterAnimInstance = Cast<UAR_AnimInstance>(Character->GetMesh()->GetAnimInstance());
    ARCHECK(CharacterAnimInstance != nullptr);
    // 애니메이션 몽타주 설정, 애님 노티파이에 호출될 함수 등록
    CharacterAnimInstance->SetAttackMontage(AttackMontage);
    CharacterAnimInstance->OnAttackStart.AddUObject(this, &ThisClass::AttackStart);
    CharacterAnimInstance->OnAttack.AddUObject(this, &ThisClass::Attack);
    CharacterAnimInstance->OnAttackEnd.AddUObject(this, &ThisClass::AttackEnd);
    // 무기에 해당하는 Input Mapping Context 등록
    AAR_PlayerController* PlayerContoller = Cast<AAR_PlayerController>(Character->GetController());
    ARCHECK(PlayerContoller != nullptr);
    ARCHECK(WeaponMappingContext != nullptr);

    PlayerContoller->AddMappingContext(WeaponMappingContext, EInputMappingPriority::Weapon);
    // 무기 장착 델리게이트 발동
    OnEquip.Broadcast();
}

void AWeaponBase::Unequip()
{
    ARCHECK(Character != nullptr);
    // Input Mapping Context 제거
    AAR_PlayerController* PlayerContoller = Cast<AAR_PlayerController>(Character->GetController());
    ARCHECK(PlayerContoller != nullptr);
    ARCHECK(WeaponMappingContext != nullptr);

    PlayerContoller->RemoveMappingContext(WeaponMappingContext);
    // 애니메이션 몽타주, 애님 노티파이 관련 정리
    CharacterAnimInstance->OnAttackStart.RemoveAll(this);
    CharacterAnimInstance->OnAttack.RemoveAll(this);
    CharacterAnimInstance->OnAttackEnd.RemoveAll(this);
    CharacterAnimInstance->SetAttackMontage(nullptr);
    CharacterAnimInstance = nullptr;
    // 소유자 해제
    SetOwner(Character = nullptr);
    // 무기 해제 델리게이트 발동
    OnUnequip.Broadcast();

    OnUnequip.Clear();
    OnEquip.Clear();
}

void AWeaponBase::LfMousePressed()
{

}

void AWeaponBase::LfMouseReleased()
{

}

void AWeaponBase::RtMousePressed()
{

}

bool AWeaponBase::CanUse()
{
    return true;
}
// AttackStart 애님 노티파이에 호출
void AWeaponBase::AttackStart()
{
    AARAGCharacter* ARAGCharacter = GetOwner<AARAGCharacter>();
    ARCHECK(ARAGCharacter != nullptr);

    UAR_CombatComponent* CombatComponent = ARAGCharacter->GetCombatComponent();
    ARCHECK(CombatComponent != nullptr);
    // 공격 중으로 설정
    CombatComponent->SetIsAttacking(true);
}
// Attack 애님 노티파이에 호출
void AWeaponBase::Attack()
{

}
// AttackEnd 애님 노티파이에 호출
void AWeaponBase::AttackEnd()
{
    AARAGCharacter* ARAGCharacter = GetOwner<AARAGCharacter>();
    ARCHECK(ARAGCharacter != nullptr);

    UAR_CombatComponent* CombatComponent = ARAGCharacter->GetCombatComponent();
    ARCHECK(CombatComponent != nullptr);
    // 공격 중이 아님으로 설정
    CombatComponent->SetIsAttacking(false);
}
