// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Die.generated.h"

/* 죽음 로직을 처리하는 Task */
UCLASS()
class ARAG_API UBTT_Die : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTT_Die();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
