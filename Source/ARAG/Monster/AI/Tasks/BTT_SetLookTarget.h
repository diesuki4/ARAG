// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetLookTarget.generated.h"

/* 설정된 타겟에 집중하도록(바라보도록) 하는 Task */
UCLASS()
class ARAG_API UBTT_SetLookTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTT_SetLookTarget();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bLookTarget;
};
