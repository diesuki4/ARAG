// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "BehaviorTree/BTTaskNode.h"
//
#include "Monster/Types/ARMonsterState.h"
//
#include "BTT_SetMonsterState.generated.h"

/* 몬스터 상태를 설정하는 Task */
UCLASS()
class ARAG_API UBTT_SetMonsterState : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTT_SetMonsterState();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EARMonsterState MonsterState;
};
