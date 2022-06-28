// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventComponent.h"
#include "GameFramework/Actor.h"

void UHorrorEventComponent::BeginPlay()
{
	Super::BeginPlay();

	if (BindActorOverlapEvent)
	{
		FScriptDelegate OnActorBeginOverlap_Delegate;
		OnActorBeginOverlap_Delegate.BindUFunction(this, FName("Multicast_CallHorrorEvent"));
		GetOwner()->OnActorBeginOverlap.Add(OnActorBeginOverlap_Delegate);
	}

	if (BindActorEndEvent)
	{
		FScriptDelegate OnActorEndOverlap_Delegate;
		OnActorEndOverlap_Delegate.BindUFunction(this, FName("Multicast_CallHorrorEvent"));
		GetOwner()->OnActorEndOverlap.Add(OnActorEndOverlap_Delegate);
	}
}

void UHorrorEventComponent::Multicast_CallHorrorEvent_Implementation(const FHorrorEventStruct& Required)
{
	for (FHorrorEventInstanced& HorrorEvent : HorrorEvents)
	{
		IHorrorEventObjectInterface::Execute_CallHorrorEvent(HorrorEvent.Instance, Required);
	}
}

