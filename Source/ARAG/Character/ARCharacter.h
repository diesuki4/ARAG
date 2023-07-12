// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ARAG.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
//
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Character/AbilitySystem/ARCharacterAbilitySystemComponent.h"
#include "DataAssets/ARActorDataAsset.h"
//
#include "ARCharacter.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UARCharacterAttributeSet;
class UARCombatComponent;

/* 메인 캐릭터 */
UCLASS(config=Game)
class AARCharacter : public ACharacter, public IAbilitySystemInterface
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
	AARCharacter(const FObjectInitializer& ObjectInitializer);

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
    // 전투 담당 컴포넌트
    UPROPERTY(VisibleAnywhere)
    UARCombatComponent* CombatComponent;

    UARCombatComponent* GetCombatComponent() { return CombatComponent; }

/* GAS */
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

    // 능력 부여 함수
    void GiveAbility(TSubclassOf<UGameplayAbility> Ability);
    void GiveAbility(TArray<TSubclassOf<UGameplayAbility>> Abilities);
    // 이펙트 적용 함수
    bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);
	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, UObject* NewSourceObject = nullptr);
    bool ApplyGameplayEffectToSelf(TArray<TSubclassOf<UGameplayEffect>> Effects, UObject* NewSourceObject = nullptr);

protected:
	UPROPERTY(EditDefaultsOnly)
	UARCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(Transient)
	UARCharacterAttributeSet* AttributeSet;

/* 액터 데이터 */
public:
	UFUNCTION(BlueprintCallable)
	FARActorData GetActorData() const;

	UFUNCTION(BlueprintCallable)
	void SetActorData(const FARActorData& InActorData);

protected:
    // 기본 액터 데이터 에셋
    UPROPERTY(EditDefaultsOnly)
    UARActorDataAsset* ActorDataAsset;
    // 현재 액터 데이터
	UPROPERTY(ReplicatedUsing = OnRep_ActorData)
	FARActorData ActorData;

	UFUNCTION()
	void OnRep_ActorData();

	virtual void InitFromActorData(const FARActorData& InActorData, bool bFromReplication = false);
};
