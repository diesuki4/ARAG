// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/ARCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//
#include "Character/AbilitySystem/ARCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Character/ActorComponents/ARCharacterMovementComponent.h"
#include "Character/ActorComponents/ARCombatComponent.h"
#include "Character/ARPlayerController.h"
#include "Character/Types/ARInputMappingPriority.h"
#include "Character/Weapons/ARWeaponBase.h"

AARCharacter::AARCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UARCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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

    CombatComponent = CreateDefaultSubobject<UARCombatComponent>(TEXT("Combat"));

	AbilitySystemComponent = CreateDefaultSubobject<UARCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UARCharacterAttributeSet>(TEXT("AttributeSet"));
}

void AARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ARCHECK(IsValid(ActorDataAsset));

	SetActorData(ActorDataAsset->ActorData);
}

void AARCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

    // 데이터 에셋으로부터 기본 GAS 능력 부여
    GiveAbility(ActorData.Abilities);
    // 데이터 에셋으로부터 기본 GAS 이펙트 적용
    ApplyGameplayEffectToSelf(ActorData.Effects);
}

void AARCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AARCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AARCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	ARCHECK(EnhancedInputComponent != nullptr);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AARCharacter::Move);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AARCharacter::Look);

    EnhancedInputComponent->BindAction(LfMouseAction, ETriggerEvent::Started, this, &AARCharacter::LfMousePressed);

    EnhancedInputComponent->BindAction(LfMouseAction, ETriggerEvent::Completed, this, &AARCharacter::LfMouseReleased);

    EnhancedInputComponent->BindAction(RtMouseAction, ETriggerEvent::Started, this, &AARCharacter::RtMousePressed);
}

void AARCharacter::Move(const FInputActionValue& Value)
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

void AARCharacter::Look(const FInputActionValue& Value)
{
	ARCHECK(Controller != nullptr);

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AARCharacter::LfMousePressed()
{
    ARCHECK(CombatComponent);

    CombatComponent->GetWeapon()->LfMousePressed();
}

void AARCharacter::LfMouseReleased()
{
    ARCHECK(CombatComponent);

    CombatComponent->GetWeapon()->LfMouseReleased();
}

void AARCharacter::RtMousePressed()
{
    ARCHECK(CombatComponent);

    CombatComponent->GetWeapon()->RtMousePressed();
}

void AARCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
    // 기본 Input Mapping Context 적용
    AARPlayerController* PlayerController = Cast<AARPlayerController>(Controller);
	ARCHECK(PlayerController != nullptr);

    PlayerController->ClearAllMappings();
    PlayerController->AddMappingContext(DefaultMappingContext, EARInputMappingPriority::Movement);
}

void AARCharacter::GiveAbility(TSubclassOf<UGameplayAbility> Ability)
{
    ARCHECK(AbilitySystemComponent);
    ARCHECK(HasAuthority());

    AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability));
}

void AARCharacter::GiveAbility(TArray<TSubclassOf<UGameplayAbility>> Abilities)
{
    ARCHECK(AbilitySystemComponent);
    ARCHECK(HasAuthority());

    for (auto Ability : Abilities)
    {
        GiveAbility(Ability);
    }
}

bool AARCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext)
{
    ARCHECK(GetLocalRole() == ROLE_Authority, false);
    ARCHECK(Effect.Get(), false);

    FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, InEffectContext);
    ARCHECK(SpecHandle.IsValid(), false);

    FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

    return ActiveGEHandle.WasSuccessfullyApplied();
}

bool AARCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, UObject* NewSourceObject)
{
    ARCHECK(GetLocalRole() == ROLE_Authority, false);
	ARCHECK(Effect.Get(), false);

    NewSourceObject = (NewSourceObject == nullptr) ? this : NewSourceObject;

    FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
    EffectContext.AddSourceObject(NewSourceObject);

	return ApplyGameplayEffectToSelf(Effect, EffectContext);
}

bool AARCharacter::ApplyGameplayEffectToSelf(TArray<TSubclassOf<UGameplayEffect>> Effects, UObject* NewSourceObject)
{
    ARCHECK(GetLocalRole() == ROLE_Authority, false);
    for (auto Effect : Effects) ARCHECK(Effect.Get(), false);

    NewSourceObject = (NewSourceObject == nullptr) ? this : NewSourceObject;

    FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
    EffectContext.AddSourceObject(NewSourceObject);

    bool bResult = true;

    for (auto Effect : Effects)
    {
        bResult &= ApplyGameplayEffectToSelf(Effect, EffectContext);
    }

    return bResult;
}

FARActorData AARCharacter::GetActorData() const
{
	return ActorData;
}

void AARCharacter::SetActorData(const FARActorData& InActorData)
{
	ActorData = InActorData;

	InitFromActorData(ActorData);
}

void AARCharacter::OnRep_ActorData()
{
	InitFromActorData(ActorData, true);
}

void AARCharacter::InitFromActorData(const FARActorData& InActorData, bool bFromReplication)
{

}

void AARCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AARCharacter, ActorData);
}
