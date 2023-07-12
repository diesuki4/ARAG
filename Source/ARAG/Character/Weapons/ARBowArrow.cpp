// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Weapons/ARBowArrow.h"
//
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AARBowArrow::AARBowArrow()
{
	PrimaryActorTick.bCanEverTick = false;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Box->BodyInstance.SetCollisionProfileName("Arrow");
    Box->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    Box->CanCharacterStepUpOn = ECB_No;
    RootComponent = Box;

    ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
    ArrowMesh->SetCollisionProfileName(TEXT("NoCollision"));
    ArrowMesh->SetupAttachment(RootComponent);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

    LifeSpan = 5.f;
}
