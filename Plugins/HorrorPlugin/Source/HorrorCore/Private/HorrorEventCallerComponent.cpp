// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventCallerComponent.h"
#include "HorrorEventComponent.h"
#include "HorrorEventInstance.h"
#include "HorrorEventFunctionLibrary.h"

FHorrorEventRequired UHorrorEventCallerComponent::GetRequired(TScriptInterface<IHorrorItemInterface> ItemInterface)
{
	FHorrorEventRequired Required;
	Required.Subject = GetOwner();
	Required.ItemInterface = ItemInterface;
	return Required;
}

void UHorrorEventCallerComponent::CallHorrorEvent(const FVector& Origin, const FVector& Direction, TScriptInterface<IHorrorItemInterface> ItemInterface)
{
	UHorrorEventComponent* EventComponent = nullptr;
	FHorrorEventCallStruct CallStruct;
	CallStruct.CallerComponent = this;
	CallStruct.Origin = Origin;
	CallStruct.Direction = Direction;
	if (IsValid(ItemInterface.GetObject()))
	{
		EventComponent = ItemInterface->Execute_GetHorrorComponent(ItemInterface.GetObject(), CallStruct);
	}
	else
	{
		UHorrorEventFunctionLibrary::GetHorrorEventComponent(CallStruct, DefaultRayMaxLength, EventComponent);
	}

	if (EventComponent == nullptr)
	{
		return;
	}

	FHorrorEventRequired Required = GetRequired(ItemInterface);

	for (FHorrorEventInstanced& HorrorEvent : EventComponent->GetHorrorEvents())
	{
		if (IsValid(HorrorEvent.Instance) == false ||
			HorrorEvent.Instance->IsExecuteable(Required) == false)
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
