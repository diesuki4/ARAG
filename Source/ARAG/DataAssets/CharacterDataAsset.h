// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Engine/DataAsset.h"
#include "ARAGTypes/CharacterData.h"
#include "CharacterDataAsset.generated.h"

/* BP를 위한 기본 캐릭터 이펙트, 능력의 래퍼 클래스 */
UCLASS(BlueprintType, Blueprintable)
class ARAG_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FCharacterData CharacterData;
};
