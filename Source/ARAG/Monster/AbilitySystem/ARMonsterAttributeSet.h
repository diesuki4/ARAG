// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ARMonsterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/* 몬스터 GAS 속성 */
UCLASS()
class ARAG_API UARMonsterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps (TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // 최대 체력
    UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_MaxHP)
    FGameplayAttributeData MaxHP;
    ATTRIBUTE_ACCESSORS(UARMonsterAttributeSet, MaxHP)

	// 체력
	UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UARMonsterAttributeSet, HP)

	// 이동 속도
	UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MaxMovementSpeed)
	FGameplayAttributeData MaxMovementSpeed;
	ATTRIBUTE_ACCESSORS(UARMonsterAttributeSet, MaxMovementSpeed)

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	virtual void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);

	UFUNCTION()
	virtual void OnRep_HP(const FGameplayAttributeData& OldHP);

	UFUNCTION()
	virtual void OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed);
};
