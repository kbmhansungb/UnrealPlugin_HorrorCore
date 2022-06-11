// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventCallerComponent.h"
#include "HorrorEventComponent.h"
#include "HorrorEventInstance.h"

void UHorrorEventCallerComponent::CallHorrorEvent(UHorrorEventComponent* HorrorEventComponent)
{
	FHorrorEventRequired Required;

	for (FHorrorEventInstanced& HorrorEvent : HorrorEventComponent->GetHorrorEvents())
	{
		if (!HorrorEvent.Instance)
		{
			continue;
		}

		if (HorrorEvent.Instance->IsLocalEvent())
		{
			ExecuteHorrorEvent(Required, HorrorEvent);
		}
		else
		{
			ServerRPC_CallHorrorEvent(Required, HorrorEvent);
		}
	}
}

void UHorrorEventCallerComponent::ExecuteHorrorEvent(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	if (HorrorEvent.Instance->State.IsExecuteable())
	{
		HorrorEvent.Instance->Execute(Required);
		HorrorEvent.Instance->State.Disabled = !HorrorEvent.Instance->IsItReuseable(Required);
	}
}

bool UHorrorEventCallerComponent::ServerRPC_CallHorrorEvent_Validate(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	return true;
}

void UHorrorEventCallerComponent::ServerRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	MulticastRPC_CallHorrorEvent(Required, HorrorEvent);
}

bool UHorrorEventCallerComponent::MulticastRPC_CallHorrorEvent_Validate(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	return true;
}

void UHorrorEventCallerComponent::MulticastRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	ExecuteHorrorEvent(Required, HorrorEvent);
}
