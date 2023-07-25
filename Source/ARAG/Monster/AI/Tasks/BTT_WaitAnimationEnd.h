// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_WaitAnimationEnd.generated.h"
/*
    애니메이션 종료 시까지 대기하는 Task
    (피격, 죽음)
*/
UCLASS()
class ARAG_API UBTT_WaitAnimationEnd : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTT_WaitAnimationEnd();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    bool bAnimationEnd = false;

    class UARMonsterAnimInstance* AnimInstanceCache;

    FDelegateHandle OnAnimationEndHandle;
};
