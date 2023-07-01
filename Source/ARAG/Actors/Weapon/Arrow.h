// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

class UProjectileMovementComponent;

/* 활(Bow) 무기 사용 시 화살집(Quiver Component)에서 꺼내 쏘는 화살 */
UCLASS()
class ARAG_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrow();

public:
    UPROPERTY(EditDefaultsOnly)
    class UBoxComponent* Box;

    UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* ArrowMesh;

    UPROPERTY(EditDefaultsOnly)
    UProjectileMovementComponent* ProjectileMovement;

    UProjectileMovementComponent* GetProjectileMovement() { return ProjectileMovement; }
};
