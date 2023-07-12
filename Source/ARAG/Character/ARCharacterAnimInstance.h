// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Animation/AnimInstance.h"
//
#include "Character/Types/ARMontageSectionName.h"
//
#include "ARCharacterAnimInstance.generated.h"

// 각 애님 노티파이 시 발동하는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnAttackStartDelegate);     // AttackStart
DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);          // Attack
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);       // AttackEnd

class UAnimMontage;

/* 메인 캐릭터 애님 인스턴스 */
UCLASS()
class ARAG_API UARCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    UARCharacterAnimInstance();

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    void SetAttackMontage(UAnimMontage* NewAttackMontage);
    void PlayAttackMontage();
    EARMontageSectionName GetCurrentSection();                           // 현재 섹션을 열거형으로 가져오기
    void JumpToMontageSection(EARMontageSectionName NewSection);
    FName GetAttackMontageSectionName(EARMontageSectionName Section);    // 열거형을 통해 섹션 이름 가져오기

    FOnAttackStartDelegate OnAttackStart;
    FOnAttackDelegate OnAttack;
    FOnAttackEndDelegate OnAttackEnd;
    // 현재 섹션
    EARMontageSectionName CurrentSection;

private:
    // 무기 장착 시 설정되는 무기별 애니메이션 몽타주
    UAnimMontage* AttackMontage;
    // 좌클릭을 누를 때 재생되는 섹션 이름
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
    FName LfMousePressedSectionName = FName(TEXT("LfMousePressed"));
    // 좌클릭을 뗄 때 재생되는 섹션 이름
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
    FName LfMouseReleasedSectionName = FName(TEXT("LfMouseReleased"));
    // 우클릭을 누를 때 재생되는 섹션 이름
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
    FName RtMousePressedSectionName = FName(TEXT("RtMousePressed"));

    UFUNCTION()
    void AnimNotify_AttackStart();

    UFUNCTION()
    void AnimNotify_AttackEnd();

    UFUNCTION()
    void AnimNotify_Attack();
};
