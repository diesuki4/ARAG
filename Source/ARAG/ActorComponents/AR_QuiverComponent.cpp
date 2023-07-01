// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AR_QuiverComponent.h"
#include "Actors/Weapon/Arrow.h"
#include "Engine/StaticMeshSocket.h"

UAR_QuiverComponent::UAR_QuiverComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    SetCollisionProfileName(TEXT("NoCollision"));

    Arrows = 0;
    MaxArrows = 10;

    ArrowBaseSocket = TEXT("ArrowBase");
}

void UAR_QuiverComponent::BeginPlay()
{
    Super::BeginPlay();

    for (int32 i = 0; i < MaxArrows; ++i)
    {
        AArrow* NewArrow = GetWorld()->SpawnActor<AArrow>(ArrowClass);

        AttachArrow(NewArrow);
        ArrowActors.Add(NewArrow);
    }

    SetArrows(MaxArrows);
}
// 화살 목록에서 화살 제거
void UAR_QuiverComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (int32 i = 0; i < ArrowActors.Num(); ++i)
    {
        if (ArrowActors[i] != nullptr)
        {
            GetWorld()->DestroyActor(ArrowActors[i]);
            ArrowActors[i] = nullptr;
        }
    }

    ArrowActors.Empty();

    Super::EndPlay(EndPlayReason);
}

bool UAR_QuiverComponent::SetArrows(int32 NewArrows)
{
    NewArrows = FMath::Clamp<int32>(NewArrows, 0, MaxArrows);

    if (NewArrows == Arrows)
        return false;

    Arrows = NewArrows;
    OnArrowsChanged.Broadcast();    // 화살 개수 변경 델리게이트 발동

    if (Arrows <= 0)
    {
        Arrows = 0;
        OnArrowsIsZero.Broadcast();     // 화살 개수 0개 델리게이트 발동
    }

    return true;
}

int32 UAR_QuiverComponent::GetArrows() const
{
    return Arrows;
}

bool UAR_QuiverComponent::CanPick() const
{
    return (0 < Arrows);
}

AArrow* UAR_QuiverComponent::Pick()
{
    if (SetArrows(Arrows - 1))
    {
        ArrowActors.Last()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

        return ArrowActors.Pop();
    }

    return nullptr;
}

bool UAR_QuiverComponent::Put(AArrow* NewArrow)
{
    if (SetArrows(Arrows + 1))
    {
        // 전달된 화살이 없으면
        if (NewArrow == nullptr)
        {
            // 새로 생성해서 넣기
            NewArrow = GetWorld()->SpawnActor<AArrow>(ArrowClass);
        }

        AttachArrow(NewArrow);
        ArrowActors.Add(NewArrow);

        return true;
    }

    return false;
}

void UAR_QuiverComponent::AttachArrow(AArrow* NewArrow)
{
    ARCHECK(NewArrow != nullptr);
    ARCHECK(DoesSocketExist(ArrowBaseSocket));

    FVector RandomPos = FVector(FMath::RandRange(-5.f, 5.f), FMath::RandRange(-4.f, 4.f), FMath::RandRange(-3.f, 3.f));
    FRotator RandomRot = FRotator(FMath::RandRange(-5.f, 5.f), 0.f, FMath::RandRange(-5.f, 5.f));

    NewArrow->SetActorRelativeLocation(RandomPos);
    NewArrow->SetActorRelativeRotation(RandomRot);

    NewArrow->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform, ArrowBaseSocket);
}
