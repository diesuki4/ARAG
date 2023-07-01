// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARAGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "AbilitySystem/AttributeSets/AR_AttributeSetBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DataAssets/CharacterDataAsset.h"
#include "Net/UnrealNetwork.h"
#include "ActorComponents/AR_CharacterMovementComponent.h"
#include "ActorComponents/AR_CombatComponent.h"
#include "AR_PlayerController.h"
#include "ARAGTypes/InputMappingPriority.h"
#include "Actors/Weapon//WeaponBase.h"

AARAGCharacter::AARAGCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UAR_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->SetRelativeLocation(FVector(30.f, 0.f, 200.f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
    FollowCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GIDEON(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Mephisto/Meshes/Gideon_Mephisto.Gideon_Mephisto'"));

    if (SK_GIDEON.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(SK_GIDEON.Object);
    }

    CombatComponent = CreateDefaultSubobject<UAR_CombatComponent>(TEXT("Combat"));

	AbilitySystemComponent = CreateDefaultSubobject<UAR_AbilitySystemComponentBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAR_AttributeSetBase>(TEXT("AttributeSet"));
}

void AARAGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ARCHECK(IsValid(CharacterDataAsset));

	SetCharacterData(CharacterDataAsset->CharacterData);
}

void AARAGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

    // 데이터 에셋으로부터 기본 캐릭터 능력 부여
	GiveAbilities();
    // 데이터 에셋으로부터 기본 캐릭터 이펙트 적용
	ApplyStartupEffects();
}

void AARAGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AARAGCharacter::BeginPlay()
{
    Super::BeginPlay();

}

void AARAGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	ARCHECK(EnhancedInputComponent != nullptr);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AARAGCharacter::Move);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AARAGCharacter::Look);

    EnhancedInputComponent->BindAction(LfMouseAction, ETriggerEvent::Started, this, &AARAGCharacter::LfMousePressed);

    EnhancedInputComponent->BindAction(LfMouseAction, ETriggerEvent::Completed, this, &AARAGCharacter::LfMouseReleased);

    EnhancedInputComponent->BindAction(RtMouseAction, ETriggerEvent::Started, this, &AARAGCharacter::RtMousePressed);
}

void AARAGCharacter::Move(const FInputActionValue& Value)
{
	ARCHECK(Controller != nullptr);

	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AARAGCharacter::Look(const FInputActionValue& Value)
{
	ARCHECK(Controller != nullptr);

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AARAGCharacter::LfMousePressed()
{
    ARCHECK(CombatComponent);

    CombatComponent->GetWeapon()->LfMousePressed();
}

void AARAGCharacter::LfMouseReleased()
{
    ARCHECK(CombatComponent);

    CombatComponent->GetWeapon()->LfMouseReleased();
}

void AARAGCharacter::RtMousePressed()
{
    ARCHECK(CombatComponent);

    CombatComponent->GetWeapon()->RtMousePressed();
}

void AARAGCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
    // 기본 Input Mapping Context 적용
    AAR_PlayerController* PlayerController = Cast<AAR_PlayerController>(Controller);
	ARCHECK(PlayerController != nullptr);

    PlayerController->ClearAllMappings();
    PlayerController->AddMappingContext(DefaultMappingContext, EInputMappingPriority::Movement);
}

bool AARAGCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext)
{
	ARCHECK(Effect.Get(), false);

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, InEffectContext);
	ARCHECK(SpecHandle.IsValid(), false);

	FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	return ActiveGEHandle.WasSuccessfullyApplied();
}

void AARAGCharacter::GiveAbilities()
{
	ARCHECK(AbilitySystemComponent);

	if (HasAuthority())
	{
		for (auto DefaultAbility : CharacterData.Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DefaultAbility));
		}
	}
}

void AARAGCharacter::ApplyStartupEffects()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (auto CharacterEffect : CharacterData.Effects)
		{
			ApplyGameplayEffectToSelf(CharacterEffect, EffectContext);
		}
	}
}

FCharacterData AARAGCharacter::GetCharacterData() const
{
	return CharacterData;
}

void AARAGCharacter::SetCharacterData(const FCharacterData& InCharacterData)
{
	CharacterData = InCharacterData;

	InitFromCharacterData(CharacterData);
}

void AARAGCharacter::OnRep_CharacterData()
{
	InitFromCharacterData(CharacterData, true);
}

void AARAGCharacter::InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication)
{

}

void AARAGCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AARAGCharacter, CharacterData);
}
