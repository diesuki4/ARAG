// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Character/Weapons/ARWeaponSkeletalBase.h"
#include "ARSword.generated.h"
/*
    검 무기 (AR Weapon Base - AR Weapon Static Base - AR Sword)
*/
UCLASS()
class ARAG_API AARSword : public AARWeaponSkeletalBase
{
	GENERATED_BODY()

public:
    AARSword();

public:
    virtual void LfMousePressed() override;      // 좌클릭 누를 시 호출  Attack()

protected:
    virtual void Attack() override;  // Attack 애님 노티파이 시 호출되는 함수
};
