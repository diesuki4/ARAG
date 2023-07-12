// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Engine/DataAsset.h"
//
#include "DataAssets/ARActorData.h"
//
#include "ARActorDataAsset.generated.h"

/* 데이터 에셋 BP를 위한 액터 데이터 래퍼 클래스 */
UCLASS(BlueprintType, Blueprintable)
class ARAG_API UARActorDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FARActorData ActorData;
};
