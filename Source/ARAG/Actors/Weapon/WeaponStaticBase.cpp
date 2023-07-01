// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/WeaponStaticBase.h"

AWeaponStaticBase::AWeaponStaticBase()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

    RootComponent = StaticMeshComponent;
}

void AWeaponStaticBase::Equip(AARAGCharacter* NewCharacter)
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

void AWeaponStaticBase::Unequip()
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
