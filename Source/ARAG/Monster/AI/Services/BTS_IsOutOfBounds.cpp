// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Services/BTS_IsOutOfBounds.h"
//
#include "Monster/ARMonsterBase.h"
#include "Monster/ARMonsterController.h"
#include "Monster/Types/ARMonsterState.h"
#include "Monster/DataAssets/ARMonsterDataAsset.h"
#include "ActorComponents/ARDataComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_IsOutOfBounds::UBTS_IsOutOfBounds()
{
    NodeName = TEXT("Is Out Of Bounds");
    Interval = 1.0F;
}

void UBTS_IsOutOfBounds::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AARMonsterController* MonsterController = Cast<AARMonsterController>(OwnerComp.GetAIOwner());
    ARCHECK(MonsterController != nullptr);

    AARMonsterBase* Monster = Cast<AARMonsterBase>(MonsterController->GetPawn());
    ARCHECK(Monster != nullptr);

    UARDataComponent* DataComponent = Monster->GetDataComponent();
    ARCHECK(DataComponent != nullptr);
    // 데이터 에셋으로부터 속성을 가져온다.
    UARMonsterDataAsset* MonsterData = Cast<UARMonsterDataAsset>(DataComponent->GetActorData());

    FVector OriginLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AARMonsterController::OriginLocationKey);
    // 초기 위치로부터 데이터 에셋의 MaxTraceDistance 거리를 벗어났는지 확인한다.
    if ((MonsterData->MaxTraceDistance * MonsterData->MaxTraceDistance) < FVector::DistSquared(OriginLocation, Monster->GetActorLocation()))
    {
        Monster->SetState(EARMonsterState::Return);
    }
}
