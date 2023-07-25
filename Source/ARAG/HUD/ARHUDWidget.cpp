// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/ARHUDWidget.h"
#include "Components/Image.h"

void UARHUDWidget::SetUIVisibility(EARCharacterUI InType, ESlateVisibility bNewVisibility)
{
    UWidget* Widget = nullptr;

    switch (InType)
    {
    case EARCharacterUI::Crosshair: Widget = Crosshair; break;
    }

    ARCHECK(Widget != nullptr);

    Widget->SetVisibility(bNewVisibility);
}
