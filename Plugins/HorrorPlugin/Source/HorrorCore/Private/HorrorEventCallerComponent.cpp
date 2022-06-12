// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventCallerComponent.h"
#include "HorrorEventComponent.h"
#include "HorrorEventInstance.h"

FHorrorEventRequired UHorrorEventCallerComponent::GetRequired()
{
	FHorrorEventRequired Required;
	Required.Subject = GetOwner();
	return Required;
}

void UHorrorEventCallerComponent::CallHorrorEvent(UHorrorEventComponent* HorrorEventComponent)
{
	FHorrorEventRequired Required = GetRequired();

	for (FHorrorEventInstanced& HorrorEvent : HorrorEventComponent->GetHorrorEvents())
	{
		if (IsValid(HorrorEvent.Instance) == false ||
			HorrorEvent.Instance->GetState().IsExecuteable() == false)
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
	HorrorEvent.Instance->Execute(Required);
}

bool UHorrorEventCallerComponent::ServerRPC_CallHorrorEvent_Validate(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	return true;
}

void UHorrorEventCallerComponent::ServerRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	MulticastRPC_CallHorrorEvent(Required, HorrorEvent);
}

void UHorrorEventCallerComponent::MulticastRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent)
{
	ExecuteHorrorEvent(Required, HorrorEvent);
}
