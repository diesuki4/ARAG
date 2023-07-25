// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTService.h"
#include "BTS_IsOutOfBounds.generated.h"

/* 추격 시 최대 이동 반경을 벗어났는지 확인하는 Service */
UCLASS()
class ARAG_API UBTS_IsOutOfBounds : public UBTService
{
	GENERATED_BODY()

public:
    UBTS_IsOutOfBounds();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
