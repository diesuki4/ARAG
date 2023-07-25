// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_FindPatrolLocation.generated.h"

/* 다음 Patrol 목적지를 찾는 Task */
UCLASS()
class ARAG_API UBTT_FindPatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UBTT_FindPatrolLocation();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
