// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTService.h"
#include "BTS_IsCloseToPlayer.generated.h"

/* 추격 시 공격할 수 있을 만큼 타겟에 가까워졌는지 확인하는 Service */
UCLASS()
class ARAG_API UBTS_IsCloseToPlayer : public UBTService
{
	GENERATED_BODY()

public:
    UBTS_IsCloseToPlayer();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
