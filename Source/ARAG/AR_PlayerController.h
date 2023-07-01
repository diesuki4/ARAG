// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "GameFramework/PlayerController.h"
#include "ARAGTypes/InputMappingPriority.h"
#include "AR_PlayerController.generated.h"

class UInputMappingContext;

/* 메인 플레이어 컨트롤러 */
UCLASS()
class ARAG_API AAR_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AAR_PlayerController();

    void ClearAllMappings();
    void AddMappingContext(UInputMappingContext* NewMappingContext, EInputMappingPriority Priority);
    void RemoveMappingContext(UInputMappingContext* MappingContext);
};
