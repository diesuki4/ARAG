// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ARAG.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Components/AR_AbilitySystemComponentBase.h"
#include "InputActionValue.h"
#include "ARAGTypes/CharacterData.h"
#include "ARAGCharacter.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UAR_AttributeSetBase;
class UAR_CombatComponent;

/* 메인 캐릭터 */
UCLASS(config=Game)
class AARAGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
    // 마우스 좌버튼 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LfMouseAction;
    // 마우스 우버튼 입력
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* RtMouseAction;

public:
	AARAGCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PawnClientRestart() override;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
    void LfMousePressed();
    void LfMouseReleased();
    void RtMousePressed();

public:
    UPROPERTY(VisibleAnywhere)
    UAR_CombatComponent* CombatComponent;

    UAR_CombatComponent* GetCombatComponent() { return CombatComponent; }

/* GAS */
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);

protected:
	UPROPERTY(EditDefaultsOnly)
	UAR_AbilitySystemComponentBase* AbilitySystemComponent;

	UPROPERTY(Transient)
	UAR_AttributeSetBase* AttributeSet;

	void GiveAbilities();           // 캐릭터 데이터로부터 기본 능력 부여
	void ApplyStartupEffects();     // 캐릭터 데이터로부터 기본 이펙트 적용

/* 캐릭터 데이터 */
public:
	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterData& InCharacterData);

protected:
    // 기본 캐릭터 데이터 에셋
    UPROPERTY(EditDefaultsOnly)
    class UCharacterDataAsset* CharacterDataAsset;
    // 현재 캐릭터 데이터
	UPROPERTY(ReplicatedUsing = OnRep_CharacterData)
	FCharacterData CharacterData;

	UFUNCTION()
	void OnRep_CharacterData();

	virtual void InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication = false);
};
