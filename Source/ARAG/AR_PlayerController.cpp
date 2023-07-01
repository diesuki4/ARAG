// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AAR_PlayerController::AAR_PlayerController()
{

}

// Clear All Input Mapping Context
void AAR_PlayerController::ClearAllMappings()
{
    UEnhancedInputLocalPlayerSubsystem* EILPSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    ARCHECK(EILPSubsystem != nullptr);

    EILPSubsystem->ClearAllMappings();
}

// Add Input Mapping Context
void AAR_PlayerController::AddMappingContext(UInputMappingContext* NewMappingContext, EInputMappingPriority Priority)
{
    ARCHECK(NewMappingContext != nullptr);

    UEnhancedInputLocalPlayerSubsystem* EILPSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    ARCHECK(EILPSubsystem != nullptr);

    EILPSubsystem->AddMappingContext(NewMappingContext, (int32)Priority);
}

// Remove Input Mapping Context
void AAR_PlayerController::RemoveMappingContext(UInputMappingContext* MappingContext)
{
    ARCHECK(MappingContext != nullptr);

    UEnhancedInputLocalPlayerSubsystem* EILPSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    ARCHECK(EILPSubsystem != nullptr);

    EILPSubsystem->RemoveMappingContext(MappingContext);
}
