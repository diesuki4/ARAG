// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Actors/Weapon/WeaponBase.h"
#include "WeaponSkeletalBase.generated.h"
/*
    Skeletal Mesh를 메시로 갖는 무기
    (WeaponBase - WeaponSkeletalBase)
*/
UCLASS()
class ARAG_API AWeaponSkeletalBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
    AWeaponSkeletalBase();

public:
    virtual void Equip(AARAGCharacter* NewCharacter) override;
    virtual void Unequip() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = true))
    USkeletalMeshComponent* SkeletalMeshComponent;
};
