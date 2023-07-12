// Fill out your copyright notice in the Description page of Project Settings.

#include "ARGameInstance.h"
//
#include "AbilitySystemGlobals.h"

void UARGameInstance::Init()
{
    Super::Init();
    // GAS 초기화
    UAbilitySystemGlobals::Get().InitGlobalData();
}
