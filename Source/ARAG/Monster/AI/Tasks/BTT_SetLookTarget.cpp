// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Tasks/BTT_SetLookTarget.h"
//
#include "Monster/ARMonsterController.h"
#include "Character/ARCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_SetLookTarget::UBTT_SetLookTarget()
{
    NodeName = TEXT("Set Look Target");
}

EBTNodeResult::Type UBTT_SetLookTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    ARCHECK(Result == EBTNodeResult::Succeeded, Result);

    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr, EBTNodeResult::Failed);

    // 현재 타겟에 집중하도록(바라보도록) 설정
    if (bLookTarget)
    {
        UObject* CurrentTarget = OwnerComp.GetBlackboardComponent()->GetValueAsObject(AARMonsterController::TargetActorKey);
        ARCHECK(CurrentTarget != nullptr, EBTNodeResult::Failed);

        AARCharacter* TargetCharacter = Cast<AARCharacter>(CurrentTarget);
        ARCHECK(TargetCharacter != nullptr, EBTNodeResult::Failed);

        MonsterController->SetFocus(TargetCharacter, EAIFocusPriority::Gameplay);
    }
    // 타겟에 집중하지 않도록 설정
    else
    {
        MonsterController->SetFocus(nullptr, EAIFocusPriority::Gameplay);
    }

    return EBTNodeResult::Succeeded;
}
