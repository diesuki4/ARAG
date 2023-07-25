// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Tasks/BTT_SetMonsterState.h"
//
#include "Monster/ARMonsterController.h"
#include "Monster/ARMonsterBase.h"

UBTT_SetMonsterState::UBTT_SetMonsterState()
{
    NodeName = TEXT("Set State (State)");
}

EBTNodeResult::Type UBTT_SetMonsterState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    ARCHECK(Result == EBTNodeResult::Succeeded, Result);

    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr, EBTNodeResult::Failed);

    AARMonsterBase* Monster = Cast<AARMonsterBase>(MonsterController->GetPawn());
    ARCHECK(Monster != nullptr, EBTNodeResult::Failed);
    // 몬스터 상태 설정
    Monster->SetState(MonsterState);

    return EBTNodeResult::Succeeded;
}
