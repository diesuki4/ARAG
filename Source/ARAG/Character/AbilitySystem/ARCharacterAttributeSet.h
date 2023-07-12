// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ARCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/* 캐릭터 GAS 속성 */
UCLASS()
class ARAG_API UARCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps (TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // 최대 체력
    UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_MaxHP)
    FGameplayAttributeData MaxHP;
    ATTRIBUTE_ACCESSORS(UARCharacterAttributeSet, MaxHP)

	// 체력
	UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UARCharacterAttributeSet, HP)

    // 최대 마나
    UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_MaxMP)
    FGameplayAttributeData MaxMP;
    ATTRIBUTE_ACCESSORS(UARCharacterAttributeSet, MaxMP)

	// 마나
	UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_MP)
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UARCharacterAttributeSet, MP)

	// 이동 속도
	UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MaxMovementSpeed)
	FGameplayAttributeData MaxMovementSpeed;
	ATTRIBUTE_ACCESSORS(UARCharacterAttributeSet, MaxMovementSpeed)

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	virtual void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);

	UFUNCTION()
	virtual void OnRep_HP(const FGameplayAttributeData& OldHP);

	UFUNCTION()
	virtual void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP);

	UFUNCTION()
	virtual void OnRep_MP(const FGameplayAttributeData& OldMP);

	UFUNCTION()
	virtual void OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed);
};
