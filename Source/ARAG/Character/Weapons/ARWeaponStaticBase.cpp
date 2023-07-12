// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Weapons/ARWeaponStaticBase.h"

AARWeaponStaticBase::AARWeaponStaticBase()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

    RootComponent = StaticMeshComponent;
}

void AARWeaponStaticBase::Equip(AARCharacter* NewCharacter)
{
    Super::Equip(NewCharacter);

    USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
    ARCHECK(CharacterMesh != nullptr);
    // 캐릭터 메시에 무기 장착
    if (CharacterMesh->DoesSocketExist(WeaponSocket))
    {
        FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;

        AttachToComponent(CharacterMesh, AttachmentTransformRules, WeaponSocket);
    }
}

void AARWeaponStaticBase::Unequip()
{
    USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
    ARCHECK(CharacterMesh != nullptr);
    // 캐릭터 메시에서 무기 해제
    if (CharacterMesh->DoesSocketExist(WeaponSocket))
    {
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    }

    Super::Unequip();
}
