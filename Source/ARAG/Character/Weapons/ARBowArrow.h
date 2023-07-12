// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "GameFramework/Actor.h"
#include "ARBowArrow.generated.h"

class UProjectileMovementComponent;

/* 활(AR Bow) 무기 사용 시 화살집(AR Quiver Component)에서 꺼내 쏘는 화살 */
UCLASS()
class ARAG_API AARBowArrow : public AActor
{
	GENERATED_BODY()
	
public:	
    AARBowArrow();

public:
    UPROPERTY(EditDefaultsOnly)
    class UBoxComponent* Box;

    UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* ArrowMesh;

    UPROPERTY(EditDefaultsOnly)
    UProjectileMovementComponent* ProjectileMovement;

    UProjectileMovementComponent* GetProjectileMovement() { return ProjectileMovement; }

    float GetArrowLifeSpan() const { return LifeSpan; }

protected:
    // 파괴 수명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Arrow, meta = (AllowPrivateAccess = true))
    float LifeSpan;
};
