// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Weapons/ARWeaponBase.h"
//
#include "Character/ARPlayerController.h"
#include "Character/Types/ARInputMappingPriority.h"
#include "Character/ActorComponents/ARCombatComponent.h"

AARWeaponBase::AARWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AARWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARWeaponBase::Equip(AARCharacter* NewCharacter)
{
    ARCHECK(NewCharacter != nullptr);
    // 소유자 설정
    SetOwner(Character = NewCharacter);

    CharacterAnimInstance = Cast<UARCharacterAnimInstance>(Character->GetMesh()->GetAnimInstance());
    ARCHECK(CharacterAnimInstance != nullptr);
    // 애니메이션 몽타주 설정, 애님 노티파이에 호출될 함수 등록
    CharacterAnimInstance->SetAttackMontage(AttackMontage);
    CharacterAnimInstance->OnAttackStart.AddUObject(this, &ThisClass::AttackStart);
    CharacterAnimInstance->OnAttack.AddUObject(this, &ThisClass::Attack);
    CharacterAnimInstance->OnAttackEnd.AddUObject(this, &ThisClass::AttackEnd);
    // 무기에 해당하는 Input Mapping Context 등록
    AARPlayerController* PlayerContoller = Cast<AARPlayerController>(Character->GetController());
    ARCHECK(PlayerContoller != nullptr);
    ARCHECK(WeaponMappingContext != nullptr);

    PlayerContoller->AddMappingContext(WeaponMappingContext, EARInputMappingPriority::Weapon);
    // 무기 장착 델리게이트 발동
    OnEquip.Broadcast();
}

void AARWeaponBase::Unequip()
{
    ARCHECK(Character != nullptr);
    // Input Mapping Context 제거
    AARPlayerController* PlayerContoller = Cast<AARPlayerController>(Character->GetController());
    ARCHECK(PlayerContoller != nullptr);
    ARCHECK(WeaponMappingContext != nullptr);
    ARCHECK(CharacterAnimInstance != nullptr);

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

void AARWeaponBase::LfMousePressed()
{

}

void AARWeaponBase::LfMouseReleased()
{

}

void AARWeaponBase::RtMousePressed()
{

}

bool AARWeaponBase::CanUse()
{
    return true;
}
// AttackStart 애님 노티파이에 호출
void AARWeaponBase::AttackStart()
{
    ARCHECK(Character != nullptr);

    UARCombatComponent* CombatComponent = Character->GetCombatComponent();
    ARCHECK(CombatComponent != nullptr);
    // 공격 중으로 설정
    CombatComponent->SetIsAttacking(true);
}
// Attack 애님 노티파이에 호출
void AARWeaponBase::Attack()
{

}
// AttackEnd 애님 노티파이에 호출
void AARWeaponBase::AttackEnd()
{
    ARCHECK(Character != nullptr);

    UARCombatComponent* CombatComponent = Character->GetCombatComponent();
    ARCHECK(CombatComponent != nullptr);
    // 공격 중이 아님으로 설정
    CombatComponent->SetIsAttacking(false);
}
