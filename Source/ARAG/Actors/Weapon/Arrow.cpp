// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/Arrow.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = false;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    RootComponent = Box;

    ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
    ArrowMesh->SetCollisionProfileName(TEXT("NoCollision"));
    ArrowMesh->SetupAttachment(RootComponent);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}
