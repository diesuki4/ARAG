// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ActorComponents/ARCombatComponent.h"
// 임시 코드
#include "Character/ARCharacter.h"
#include "Character/Weapons/ARWeaponBase.h"

UARCombatComponent::UARCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UARCombatComponent::BeginPlay()
{
	Super::BeginPlay();
    // 임시 코드
    ARCHECK(DefaultWeapon != nullptr);
    CurrentWeapon = GetWorld()->SpawnActor<AARWeaponBase>(DefaultWeapon);
    CurrentWeapon->Equip(GetOwner<AARCharacter>());
    CurrentWeapon->Unequip();
    CurrentWeapon->Equip(GetOwner<AARCharacter>());
}

void UARCombatComponent::SetWeapon(AARWeaponBase* NewWeapon)
{
    CurrentWeapon = NewWeapon;
}

bool UARCombatComponent::CanAttack()
{
    ARCHECK(CurrentWeapon != nullptr, false);

    AARCharacter* Character = Cast<AARCharacter>(CurrentWeapon->GetOwner());
    ARCHECK(Character != nullptr, false);

    return (Character->GetState() == EARCharacterState::Normal);
}
