// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Components/ActorComponent.h"
#include "ARCombatComponent.generated.h"

class AARWeaponBase;

/* 캐릭터 전투 담당 컴포넌트 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARAG_API UARCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UARCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
    void SetWeapon(AARWeaponBase* NewWeapon);
    AARWeaponBase* GetWeapon() { return CurrentWeapon; }

    bool CanAttack();
    void SetIsAttacking(bool NewIsAttacking);
    bool IsAttacking() { return bIsAttacking; }

protected:
    AARWeaponBase* CurrentWeapon;

    bool bIsAttacking;
    // 임시 코드
    // 기본 무기
    UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = true))
    TSubclassOf<class AARWeaponBase> DefaultWeapon;
};
