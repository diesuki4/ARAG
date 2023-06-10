// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Engine/GameInstance.h"
#include "AR_GameInstance.generated.h"

UCLASS()
class ARAG_API UAR_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
};
