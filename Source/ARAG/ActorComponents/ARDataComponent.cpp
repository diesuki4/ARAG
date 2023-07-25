// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponents/ARDataComponent.h"
//
#include "Net/UnrealNetwork.h"

UARDataComponent::UARDataComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    SetIsReplicated(true);
}

void UARDataComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

UARActorDataAssetBase* UARDataComponent::GetActorData() const
{
    return ActorData;
}

void UARDataComponent::OnRep_ActorData()
{

}

void UARDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UARDataComponent, ActorData);
}
