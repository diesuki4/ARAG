// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Engine/GameInstance.h"
#include "ARGameInstance.generated.h"

/* 기본 게임 인스턴스 */
UCLASS()
class ARAG_API UARGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
};
