// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Tasks/BTT_FindPatrolLocation.h"
//
#include "Monster/ARMonsterBase.h"
#include "Monster/ARMonsterController.h"
#include "Monster/DataAssets/ARMonsterDataAsset.h"
#include "ActorComponents/ARDataComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_FindPatrolLocation::UBTT_FindPatrolLocation()
{
    NodeName = TEXT("Find Patrol Location");
}

EBTNodeResult::Type UBTT_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    ARCHECK(Result == EBTNodeResult::Succeeded, Result);

    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr, EBTNodeResult::Failed);

    AARMonsterBase* Monster = Cast<AARMonsterBase>(MonsterController->GetPawn());
    ARCHECK(Monster != nullptr, EBTNodeResult::Failed);

    UARDataComponent* DataComponent = Monster->GetDataComponent();
    ARCHECK(DataComponent != nullptr, EBTNodeResult::Failed);
    // 데이터 에셋으로부터 속성을 가져온다.
    UARMonsterDataAsset* MonsterData = Cast<UARMonsterDataAsset>(DataComponent->GetActorData());

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Monster->GetWorld());
    ARCHECK(NavSystem != nullptr, EBTNodeResult::Failed);

    FVector OriginLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AARMonsterController::OriginLocationKey);
    FNavLocation NextPatrol;
    // 초기 위치로부터 데이터 에셋의 PatrolDistance 내의 위치로 설정한다.
    if (NavSystem->GetRandomPointInNavigableRadius(OriginLocation, MonsterData->PatrolDistance, NextPatrol))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(AARMonsterController::PatrolLocationKey, NextPatrol.Location);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
