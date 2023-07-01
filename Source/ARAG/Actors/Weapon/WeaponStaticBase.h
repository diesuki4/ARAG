// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Actors/Weapon/WeaponBase.h"
#include "WeaponStaticBase.generated.h"
/*
    Static Mesh를 메시로 갖는 무기
    (WeaponBase - WeaponStaticBase)
*/
UCLASS()
class ARAG_API AWeaponStaticBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
    AWeaponStaticBase();

public:
    virtual void Equip(AARAGCharacter* NewCharacter) override;
    virtual void Unequip() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* StaticMeshComponent;
};
