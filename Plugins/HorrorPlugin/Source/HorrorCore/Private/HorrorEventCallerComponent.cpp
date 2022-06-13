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

	UE_LOG(LogTemp, Display, TEXT("Actor is called"));
	FHorrorEventStruct Required = FHorrorEventStruct(GetOwner(), HitResult.Actor.Get(), ItemInterface, Origin, Direction);
	//ServerRPC_CallHorrorEvent(Required);

	UHorrorEventComponent* EventComponent = Cast<UHorrorEventComponent>(Required.Object->GetComponentByClass(UHorrorEventComponent::StaticClass()));
	if (EventComponent == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("EventComponent is not valid"));
		return;
	}

	for (FHorrorEventInstanced& HorrorEvent : EventComponent->GetHorrorEvents())
	{
		if (IsValid(HorrorEvent.Instance) == false ||
			HorrorEvent.Instance->IsExecuteable(Required) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("Instance is not valid %s"), *HorrorEvent.Instance->GetName());
			continue;
		}

		if (HorrorEvent.Instance->IsLocalEvent())
		{
			UE_LOG(LogTemp, Display, TEXT("Local is called"));
			HorrorEvent.Instance->Execute(Required);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Multicast is called"));
			ServerRPC_CallHorrorEvent(Required, HorrorEvent);
		}
	}
}

bool UHorrorEventCallerComponent::ServerRPC_CallHorrorEvent_Validate(const FHorrorEventStruct& Required, const FHorrorEventInstanced& HorrorEvent)
{
	return true;
}

void UHorrorEventCallerComponent::ServerRPC_CallHorrorEvent_Implementation(const FHorrorEventStruct& Required, const FHorrorEventInstanced& HorrorEvent)
{
	MulticastRPC_CallHorrorEventInstanced(Required, HorrorEvent);
}

void UHorrorEventCallerComponent::MulticastRPC_CallHorrorEventInstanced_Implementation(const FHorrorEventStruct& Required, const FHorrorEventInstanced& HorrorEvent)
{
	HorrorEvent.Instance->Execute(Required);
}

