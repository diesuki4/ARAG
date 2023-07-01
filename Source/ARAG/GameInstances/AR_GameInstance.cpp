// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/AR_GameInstance.h"

#include "AbilitySystemGlobals.h"

void UAR_GameInstance::Init()
{
    Super::Init();
    // GAS 초기화
    UAbilitySystemGlobals::Get().InitGlobalData();
}
