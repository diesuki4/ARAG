// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Attack.generated.h"

/* 공격 Task */
UCLASS()
class ARAG_API UBTT_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTT_Attack();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
