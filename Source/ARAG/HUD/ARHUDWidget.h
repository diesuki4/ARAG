// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Blueprint/UserWidget.h"
//
#include "Character/Types/ARCharacterUI.h"
//
#include "ARHUDWidget.generated.h"

/* 메인 HUD UI */
UCLASS()
class ARAG_API UARHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // 위젯별 가시성 설정
    void SetUIVisibility(EARCharacterUI InType, ESlateVisibility bNewVisibility);
	
private:
    // 발사체 무기 사용시 조준선
    UPROPERTY(meta = (BindWidget))
    class UImage* Crosshair;
};
