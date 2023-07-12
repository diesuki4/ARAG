// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Weapons/ARSword.h"
//
#include "Types/ARCollisionChannel.h"

AARSword::AARSword()
{
    AttackRange = 200.f;
    AttackRadius = 30.f;
}

void AARSword::LfMousePressed()
{
    Super::LfMousePressed();
    // Attack 애님 노티파이를 통해 Attack() 함수를 호출한다.
    ARCHECK(CharacterAnimInstance != nullptr);

    CharacterAnimInstance->PlayAttackMontage();
    CharacterAnimInstance->JumpToMontageSection(EARMontageSectionName::LfMousePressed);
}

void AARSword::Attack()
{
    Super::Attack();
    // 공격 판정 진행
    FHitResult HitResult;
    FCollisionQueryParams Params(NAME_None, false, Character);

    FVector ActorLocation = Character->GetActorLocation();
    FVector ActorForwardVector = Character->GetActorForwardVector();

    bool bResult = GetWorld()->SweepSingleByChannel(
        HitResult,
        ActorLocation, ActorLocation + ActorForwardVector * AttackRange,
        FQuat::Identity,
        AR_ECC_Attack,
        FCollisionShape::MakeSphere(AttackRadius),
        Params
    );

#if ENABLE_DRAW_DEBUG
    FVector TraceVec = ActorForwardVector * AttackRange;
    FVector Center = ActorLocation + TraceVec * 0.5f;
    float HalfHeight = AttackRange * 0.5f + AttackRadius;
    FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
    FColor DrawColor = (bResult) ? FColor::Green : FColor::Red;
    float DebugLifeTime = 5.0f;

    DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, CapsuleRot, DrawColor, false, DebugLifeTime);
#endif
    // 판정 성공했으면
    if (bResult)
    {
        // 상대 액터 데미지 처리
        AActor* Victim = HitResult.GetActor();
        ARCHECK(Victim != nullptr);

        FDamageEvent DamageEvent;
        Victim->TakeDamage(WeaponDamage, DamageEvent, Character->GetController(), Character);
    }
}
