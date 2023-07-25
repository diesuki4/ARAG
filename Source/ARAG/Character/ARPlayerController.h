// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "GameFramework/PlayerController.h"
//
#include "Character/Types/ARInputMappingPriority.h"
//
#include "ARPlayerController.generated.h"

class UInputMappingContext;
class UARHUDWidget;

/* 메인 플레이어 컨트롤러 */
UCLASS()
class ARAG_API AARPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AARPlayerController();

    void ClearAllMappings();
    void AddMappingContext(UInputMappingContext* NewMappingContext, EARInputMappingPriority Priority);
    void RemoveMappingContext(UInputMappingContext* MappingContext);

    UARHUDWidget* GetHUDWidget() const { return HUDWidget; };

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UARHUDWidget> HUDWidgetClass;

private:
    // 메인 HUD
    UPROPERTY()
    UARHUDWidget* HUDWidget;
};
