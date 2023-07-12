// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Character/Weapons/ARWeaponSkeletalBase.h"
#include "ARBow.generated.h"

class UARQuiverComponent;
/*
    활 무기 (AR Weapon Base - AR Weapon Skeletal Base - AR Bow)
*/
UCLASS()
class ARAG_API AARBow : public AARWeaponSkeletalBase
{
	GENERATED_BODY()
	
public:
    AARBow();

public:
    virtual void Equip(AARCharacter* NewCharacter) override;
    virtual void Unequip() override;

    virtual void LfMousePressed() override;      // 좌클릭 누를 시 호출  AttackStart()
    virtual void LfMouseReleased() override;     // 좌클릭 뗄 시 호출    Attack() > AttackEnd()
    virtual void RtMousePressed() override;      // 우클릭 누를 시 호출  AttackEnd()

    virtual bool CanUse();      // 현재 사용 가능한 상태인지 반환

protected:
    // 각 애님 노티파이 시 호출되는 함수
    virtual void AttackStart();  // AttackStart
    virtual void Attack();       // Attack
    virtual void AttackEnd();    // AttackEnd

    // 화살집 종류
    UPROPERTY(EditDefaultsOnly, Category = Bow, Meta = (AllowPrivateAccess = true))
    TSubclassOf<UARQuiverComponent> QuiverComponentClass;
    // 캐릭터 메시에 화살집 컴포넌트를 부착할 위치
    UPROPERTY(EditDefaultsOnly, Category = Bow, meta = (AllowPrivateAccess = true))
    FName QuiverSocket;
    // 활 공격 시 캐릭터 메시 손 부분에 화살을 붙일 위치
    UPROPERTY(EditDefaultsOnly, Category = Bow, meta = (AllowPrivateAccess = true))
    FName ArrowSocket;

    // 캐릭터에 붙인 화살집 캐싱
    UARQuiverComponent* QuiverComponent;
    // 현재 캐릭터 손에 있는 화살
    class AARBowArrow* CurrentArrow;
};
