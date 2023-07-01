// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Components/ActorComponent.h"
#include "AR_CombatComponent.generated.h"

class AWeaponBase;

/* 전투 담당 컴포넌트 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARAG_API UAR_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAR_CombatComponent();

protected:
	virtual void BeginPlay() override;

public:
    void SetWeapon(AWeaponBase* NewWeapon);
    AWeaponBase* GetWeapon() { return CurrentWeapon; }

    bool CanAttack();
    void SetIsAttacking(bool NewIsAttacking);
    bool IsAttacking() { return bIsAttacking; }

protected:
    AWeaponBase* CurrentWeapon;

    bool bIsAttacking;
    // 임시 코드
    // 기본 무기
    UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = true))
    TSubclassOf<class AWeaponBase> DefaultWeapon;
};
