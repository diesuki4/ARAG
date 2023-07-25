// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ARPlayerController.h"
//
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUD/ARHUDWidget.h"

AARPlayerController::AARPlayerController()
{

}

void AARPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameOnly());

    HUDWidget = CreateWidget<UARHUDWidget>(this, HUDWidgetClass);
    ARCHECK(HUDWidget != nullptr);

    HUDWidget->AddToViewport();
}

void AARPlayerController::ClearAllMappings()
{
    UEnhancedInputLocalPlayerSubsystem* EILPSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    ARCHECK(EILPSubsystem != nullptr);

    EILPSubsystem->ClearAllMappings();
}

void AARPlayerController::AddMappingContext(UInputMappingContext* NewMappingContext, EARInputMappingPriority Priority)
{
    ARCHECK(NewMappingContext != nullptr);

    UEnhancedInputLocalPlayerSubsystem* EILPSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    ARCHECK(EILPSubsystem != nullptr);

    EILPSubsystem->AddMappingContext(NewMappingContext, (int32)Priority);
}

void AARPlayerController::RemoveMappingContext(UInputMappingContext* MappingContext)
{
    ARCHECK(MappingContext != nullptr);

    UEnhancedInputLocalPlayerSubsystem* EILPSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    ARCHECK(EILPSubsystem != nullptr);

    EILPSubsystem->RemoveMappingContext(MappingContext);
}
