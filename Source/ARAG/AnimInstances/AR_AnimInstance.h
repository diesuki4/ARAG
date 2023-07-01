// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Animation/AnimInstance.h"
#include "AR_AnimInstance.generated.h"

// 각 애님 노티파이 시 발동하는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnAttackStartDelegate);     // AttackStart
DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);          // Attack
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);       // AttackEnd

class UAnimMontage;

/* 메인 캐릭터 애님 인스턴스 */
UCLASS()
class ARAG_API UAR_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    UAR_AnimInstance();

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    void SetAttackMontage(UAnimMontage* NewAttackMontage);
    void PlayAttackMontage();
    ESectionName GetCurrentSection();                           // 현재 섹션을 열거형으로 가져오기
    void JumpToMontageSection(ESectionName NewSection);
    FName GetAttackMontageSectionName(ESectionName Section);    // 열거형을 통해 섹션 이름 가져오기

    FOnAttackStartDelegate OnAttackStart;
    FOnAttackDelegate OnAttack;
    FOnAttackEndDelegate OnAttackEnd;
    // 현재 섹션
    ESectionName CurrentSection;

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

/* 애니메이션 몽타주 상의 섹션 이름을 매핑하기 위한 열거형 */
UENUM(BlueprintType)
enum class ESectionName : uint8
{
    LfMousePressed   UMETA(DisplayName = "LfMousePressed"),
    LfMouseReleased  UMETA(DisplayName = "LfMouseReleased"),
    RtMousePressed   UMETA(DisplayName = "RtMousePressed"),

    MAX    UMETA(DisplayName = "Default MAX")
};
