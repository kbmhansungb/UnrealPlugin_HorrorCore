// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventCallerComponent.h"
#include "HorrorEventComponent.h"
#include "HorrorEventInstance.h"
#include "GameFramework/Actor.h"
#include "HorrorEventObjectInterface.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void UHorrorEventCallerComponent::CallHorrorEvent(const FVector& Origin, const FVector& Direction)
{
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	bool IsHit = GetOwner()->GetWorld()->LineTraceSingleByObjectType(HitResult, Origin, Origin + Direction * RayMaxLength, ObjectQueryParams, QueryParams);

#if ENABLE_DRAW_DEBUG

	DrawDebugLine(GetOwner()->GetWorld(), HitResult.TraceStart,
		IsHit ? HitResult.Location : HitResult.TraceEnd,
		IsHit ? FColor::Green : FColor::Red,
		false, 1.0f);

#endif

	if (HitResult.Actor.IsValid() == false)
	{
		return;
	}

	FHorrorEventStruct Required = FHorrorEventStruct(GetOwner(), HitResult.Actor.Get(), ItemInterface, Origin, Direction);

	if (HitResult.Actor.Get()->GetClass()->ImplementsInterface(UHorrorEventObjectInterface::StaticClass()))
	{
		CallHorrorEventByInterface(HitResult.Actor.Get(), Required);
	}

	UHorrorEventComponent* EventComponent = Cast<UHorrorEventComponent>(Required.Object->GetComponentByClass(UHorrorEventComponent::StaticClass()));
	if (EventComponent)
	{
		for (FHorrorEventInstanced& HorrorEvent : EventComponent->GetHorrorEvents())
		{
			CallHorrorEventByInterface(HorrorEvent.Instance, Required);
		}
	}
}

void UHorrorEventCallerComponent::CallHorrorEventByInterface(UObject* Object, const FHorrorEventStruct& Required)
{
	if (IHorrorEventObjectInterface::Execute_IsExecuteable(Object, Required) == false)
	{
		return;
	}

	if (IHorrorEventObjectInterface::Execute_IsLocalEvent(Object, Required))
	{
		IHorrorEventObjectInterface::Execute_CallHorrorEvent(Object, Required);
	}
	else
	{
		ServerRPC_MulticastHorrorEvent(Object, Required);
	}
}

bool UHorrorEventCallerComponent::ServerRPC_MulticastHorrorEvent_Validate(UObject* Object, const FHorrorEventStruct& Required)
{
	return true;
}

void UHorrorEventCallerComponent::ServerRPC_MulticastHorrorEvent_Implementation(UObject* Object, const FHorrorEventStruct& Required)
{
	MulticastRPC_CallHorrorEvent(Object, Required);
}

void UHorrorEventCallerComponent::MulticastRPC_CallHorrorEvent_Implementation(UObject* Object, const FHorrorEventStruct& Required)
{
	IHorrorEventObjectInterface::Execute_CallHorrorEvent(Object, Required);
}

