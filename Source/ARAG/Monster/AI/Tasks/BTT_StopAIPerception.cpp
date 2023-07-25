// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Tasks/BTT_StopAIPerception.h"
//
#include "Monster/ARMonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

UBTT_StopAIPerception::UBTT_StopAIPerception()
{
    NodeName = TEXT("Stop AI Perception");
}

EBTNodeResult::Type UBTT_StopAIPerception::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    ARCHECK(Result == EBTNodeResult::Succeeded, Result);

    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr, EBTNodeResult::Failed);

    UAIPerceptionComponent* AIPerception = MonsterController->GetAIPerceptionComponent();
    // AI Perception 비활성화
    AIPerception->OnTargetPerceptionUpdated.Clear();
    AIPerception->Deactivate();

    return EBTNodeResult::Succeeded;
}
