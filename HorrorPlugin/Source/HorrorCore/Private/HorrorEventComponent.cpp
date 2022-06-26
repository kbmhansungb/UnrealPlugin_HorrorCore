// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventComponent.h"
#include "GameFramework/Actor.h"

void UHorrorEventComponent::BeginPlay()
{
	Super::BeginPlay();

	if (BindActorOverlapEvent)
	{
		FScriptDelegate OnActorBeginOverlap_Delegate;
		OnActorBeginOverlap_Delegate.BindUFunction(this, FName("CallHorrorEvent"));
		GetOwner()->OnActorBeginOverlap.Add(OnActorBeginOverlap_Delegate);
	}

	if (BindActorEndEvent)
	{
		FScriptDelegate OnActorEndOverlap_Delegate;
		OnActorEndOverlap_Delegate.BindUFunction(this, FName("CallHorrorEvent"));
		GetOwner()->OnActorEndOverlap.Add(OnActorEndOverlap_Delegate);
	}
}

void UHorrorEventComponent::CallHorrorEvent(const FHorrorEventStruct& Required)
{
	for (FHorrorEventInstanced& HorrorEvent : HorrorEvents)
	{
		IHorrorEventObjectInterface::Execute_CallHorrorEvent(HorrorEvent.Instance, Required);
	}
}

