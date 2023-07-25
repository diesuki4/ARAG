// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Tasks/BTT_WaitAnimationEnd.h"
//
#include "Monster/ARMonsterController.h"
#include "Monster/ARMonsterBase.h"
#include "Monster/ARMonsterAnimInstance.h"

UBTT_WaitAnimationEnd::UBTT_WaitAnimationEnd()
{
    bNotifyTick = true;
    NodeName = TEXT("Wait Animation End");
}

EBTNodeResult::Type UBTT_WaitAnimationEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr, EBTNodeResult::Failed);

    AARMonsterBase* Monster = Cast<AARMonsterBase>(MonsterController->GetPawn());
    ARCHECK(Monster != nullptr, EBTNodeResult::Failed);

    AnimInstanceCache = Cast<UARMonsterAnimInstance>(Monster->GetMesh()->GetAnimInstance());
    ARCHECK(AnimInstanceCache != nullptr, EBTNodeResult::Failed);
    // 피격, 죽음 애니메이션의 AnimationEnd 애님 노티파이에 수행된다.
    OnAnimationEndHandle = AnimInstanceCache->OnAnimationEnd.AddLambda([this]() { bAnimationEnd = true; });

    return EBTNodeResult::InProgress;
}

void UBTT_WaitAnimationEnd::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (bAnimationEnd)
    {
        ARCHECK(AnimInstanceCache != nullptr);

        AnimInstanceCache->OnAnimationEnd.Remove(OnAnimationEndHandle);
        bAnimationEnd = false;

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
