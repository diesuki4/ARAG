// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/Services/BTS_IsCloseToPlayer.h"
//
#include "Monster/ARMonsterBase.h"
#include "Monster/ARMonsterController.h"
#include "Monster/Types/ARMonsterState.h"
#include "Monster/DataAssets/ARMonsterDataAsset.h"
#include "ActorComponents/ARDataComponent.h"
#include "Character/ARCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_IsCloseToPlayer::UBTS_IsCloseToPlayer()
{
    NodeName = TEXT("Is Close To Player");
    Interval = 0.2F;
}

void UBTS_IsCloseToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

    UObject* CurrentTarget = OwnerComp.GetBlackboardComponent()->GetValueAsObject(AARMonsterController::TargetActorKey);
    ARCHECK(CurrentTarget != nullptr);

    AARCharacter* TargetCharacter = Cast<AARCharacter>(CurrentTarget);
    ARCHECK(TargetCharacter != nullptr);
    // 타겟과의 거리가 데이터 에셋의 AttackRange 이하이면 공격 상태로 전환
    if (FVector::DistSquared(Monster->GetActorLocation(), TargetCharacter->GetActorLocation()) <= (MonsterData->AttackRange * MonsterData->AttackRange))
    {
        Monster->SetState(EARMonsterState::Attack);
    }
}
