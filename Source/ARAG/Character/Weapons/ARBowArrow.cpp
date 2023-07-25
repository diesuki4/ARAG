// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Weapons/ARBowArrow.h"
//
#include "Character/ARCharacter.h"
#include "Character/ActorComponents/ARCombatComponent.h"
#include "Character/Weapons/ARWeaponBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AARBowArrow::AARBowArrow()
{
	PrimaryActorTick.bCanEverTick = false;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Box->BodyInstance.SetCollisionProfileName("NoCollision");
    Box->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.F));
    Box->CanCharacterStepUpOn = ECB_No;
    RootComponent = Box;

    ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
    ArrowMesh->SetCollisionProfileName(TEXT("NoCollision"));
    ArrowMesh->SetupAttachment(RootComponent);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

    LifeSpan = 5.F;
}

void AARBowArrow::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Box->OnComponentHit.AddDynamic(this, &ThisClass::OnEnemyHit);
}

void AARBowArrow::OnEnemyHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    AARCharacter* HarmerCharacter = Cast<AARCharacter>(GetOwner());
    ARCHECK(HarmerCharacter != nullptr);

    UARCombatComponent* CombatComponent = HarmerCharacter->GetCombatComponent();
    ARCHECK(CombatComponent != nullptr);

    AARWeaponBase* CurrentWeapon = CombatComponent->GetWeapon();
    ARCHECK(CurrentWeapon != nullptr);

    float AttackDamage = CurrentWeapon->GetWeaponDamage();
    // 데미지 처리 후
    FDamageEvent DamageEvent;
    OtherActor->TakeDamage(AttackDamage, DamageEvent, HarmerCharacter->GetController(), HarmerCharacter);
    // 파괴
    Destroy();
}
