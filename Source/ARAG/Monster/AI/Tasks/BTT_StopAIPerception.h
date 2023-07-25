// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_StopAIPerception.generated.h"

/* 플레이어 감지를 중단하는 Task */
UCLASS()
class ARAG_API UBTT_StopAIPerception : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UBTT_StopAIPerception();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
