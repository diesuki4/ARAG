// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponSkeletalBase.h"

AWeaponSkeletalBase::AWeaponSkeletalBase()
{
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

    RootComponent = SkeletalMeshComponent;
}

void AWeaponSkeletalBase::Equip(AARAGCharacter* NewCharacter)
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

void AWeaponSkeletalBase::Unequip()
{
    USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
    ARCHECK(CharacterMesh != nullptr);
    // 캐릭터 메시에서 무기 해제
    if (CharacterMesh->DoesSocketExist(WeaponSocket))
    {
        DetachRootComponentFromParent(true);
    }

    Super::Unequip();
}
