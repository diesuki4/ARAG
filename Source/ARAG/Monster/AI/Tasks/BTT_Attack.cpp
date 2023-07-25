// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Tasks/BTT_Attack.h"
//
#include "Monster/ARMonsterBase.h"
#include "Monster/ARMonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_Attack::UBTT_Attack()
{
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    ARCHECK(Result == EBTNodeResult::Succeeded, Result);

    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr, EBTNodeResult::Failed);

    AARMonsterBase* Monster = Cast<AARMonsterBase>(MonsterController->GetPawn());
    ARCHECK(Monster != nullptr, EBTNodeResult::Failed);
    // 공격 몽타주 재생 래퍼 함수 실행
    Monster->Attack();

    return EBTNodeResult::Succeeded;
}
