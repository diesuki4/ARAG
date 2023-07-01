// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AR_CombatComponent.h"
// 임시 코드
#include "ARAGCharacter.h"
#include "Actors/Weapon/WeaponBase.h"

UAR_CombatComponent::UAR_CombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAR_CombatComponent::BeginPlay()
{
	Super::BeginPlay();
    // 임시 코드
    CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(DefaultWeapon);
    CurrentWeapon->Equip(GetOwner<AARAGCharacter>());
    CurrentWeapon->Unequip();
    CurrentWeapon->Equip(GetOwner<AARAGCharacter>());
}

void UAR_CombatComponent::SetWeapon(AWeaponBase* NewWeapon)
{
    CurrentWeapon = NewWeapon;
}

bool UAR_CombatComponent::CanAttack()
{
    ARCHECK(CurrentWeapon != nullptr, false);

    return CurrentWeapon->CanUse();
}

void UAR_CombatComponent::SetIsAttacking(bool NewIsAttacking)
{
    bIsAttacking = NewIsAttacking;
}
