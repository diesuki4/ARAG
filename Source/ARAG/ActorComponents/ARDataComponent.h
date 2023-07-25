// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARAG.h"
#include "Components/ActorComponent.h"
//
#include "DataAssets/ARActorDataAssetBase.h"
//
#include "ARDataComponent.generated.h"
/*
    캐릭터와 몬스터의 속성을 데이터 에셋으로 관리하기 위한 컴포넌트
    (캐릭터와 몬스터 = 액터로 칭함)
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARAG_API UARDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UARDataComponent();

protected:
	virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    UFUNCTION(BlueprintCallable)
    UARActorDataAssetBase* GetActorData() const;

protected:
    // 기본 액터 데이터 에셋
    UPROPERTY(ReplicatedUsing = OnRep_ActorData, EditDefaultsOnly, BlueprintReadOnly, Category = Actor, meta = (AllowPrivateAccess = "true"))
    UARActorDataAssetBase* ActorData;

    UFUNCTION()
    void OnRep_ActorData();
};
