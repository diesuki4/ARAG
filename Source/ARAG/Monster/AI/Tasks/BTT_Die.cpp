// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Tasks/BTT_Die.h"
//
#include "Monster/ARMonsterBase.h"
#include "Monster/ARMonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_Die::UBTT_Die()
{
    NodeName = TEXT("Die");
}

EBTNodeResult::Type UBTT_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    ARCHECK(Result == EBTNodeResult::Succeeded, Result);

    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr, EBTNodeResult::Failed);

    AARMonsterBase* Monster = Cast<AARMonsterBase>(MonsterController->GetPawn());
    ARCHECK(Monster != nullptr, EBTNodeResult::Failed);
    // 파괴
    Monster->Destroy();

    return EBTNodeResult::Succeeded;
}
