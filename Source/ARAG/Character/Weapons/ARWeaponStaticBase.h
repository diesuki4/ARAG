// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Character/Weapons/ARWeaponBase.h"
#include "ARWeaponStaticBase.generated.h"
/*
    Static Mesh를 메시로 갖는 무기
    (AR Weapon Base - AR Weapon Static Base)
*/
UCLASS()
class ARAG_API AARWeaponStaticBase : public AARWeaponBase
{
	GENERATED_BODY()
	
public:
    AARWeaponStaticBase();

public:
    virtual void Equip(AARCharacter* NewCharacter) override;
    virtual void Unequip() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponStatic, meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* StaticMeshComponent;
};
