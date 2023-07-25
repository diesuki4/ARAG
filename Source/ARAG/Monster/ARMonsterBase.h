// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "GameFramework/Character.h"
//
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ARAbilitySystemComponent.h"
#include "Monster/AbilitySystem/ARMonsterAttributeSet.h"
#include "Monster/Types/ARMonsterState.h"
//
#include "ARMonsterBase.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMonsterStateChangedDelegate, EARMonsterState /*OldMonsterState*/, EARMonsterState /*NewMonsterState*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterDamagedDelegate, AActor* /*DamageCauser*/);
DECLARE_MULTICAST_DELEGATE(FOnMonsterDieDelegate);

class UARMonsterAttributeSet;
class UARDataComponent;

/* 몬스터 Base */
UCLASS()
class ARAG_API AARMonsterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
    AARMonsterBase();

    FOnMonsterStateChangedDelegate OnStateChanged;
    FOnMonsterDamagedDelegate OnDamaged;
    FOnMonsterDieDelegate OnDie;

protected:
    virtual void PostInitializeComponents() override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;
	virtual void BeginPlay() override;

    // 몬스터의 상태
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster, Meta = (AllowPrivateAccess = true))
    EARMonsterState State;
    // 임시 코드
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster, Meta = (AllowPrivateAccess = true))
    float HP;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                             class AController* EventInstigator, AActor* DamageCauser) override;
    // 공격 (몽타주 재생 래퍼 함수)
    virtual void Attack();
    // 공격 로직 수행
    virtual void OnAttackTarget();

    EARMonsterState GetState() const { return State; }
    void SetState(EARMonsterState NewState);
    // 임시 코드
    float GetHP() const { return HP; }

/* GAS */
public:
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

protected:
    UPROPERTY(EditDefaultsOnly)
    UARAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(Transient)
    UARMonsterAttributeSet* AttributeSet;

/* 몬스터 데이터 */
protected:
    UPROPERTY(VisibleAnywhere)
    UARDataComponent* DataComponent;
    // Data Component에서 가져온 데이터 캐싱
    class UARMonsterDataAsset* MonsterData;

public:
    UARDataComponent* GetDataComponent() { return DataComponent; }
};
