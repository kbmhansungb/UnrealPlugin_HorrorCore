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

#if !NO_CVARS
	static const auto DebugDrawEventCall = IConsoleManager::Get().FindConsoleVariable(TEXT("Horror.DebugDrawEventCall"));

	if (DebugDrawEventCall->GetBool())
	{
		DrawDebugLine(GetOwner()->GetWorld(), HitResult.TraceStart,
			IsHit ? HitResult.Location : HitResult.TraceEnd,
			IsHit ? FColor::Green : FColor::Red,
			false, 1.0f);
	}

#endif

#endif

	if (HitResult.Actor.IsValid() == false)
	{
		return;
	}

	FHorrorEventStruct Required = FHorrorEventStruct(GetOwner(), HitResult.Actor.Get(), ItemInterface, Origin, Direction);
	ServerRPC_MulticastHorrorEvent(HitResult.Actor.Get(), Required);
}

bool UHorrorEventCallerComponent::ServerRPC_MulticastHorrorEvent_Validate(AActor* Actor, const FHorrorEventStruct& Required)
{
	return true;
}

void UHorrorEventCallerComponent::ServerRPC_MulticastHorrorEvent_Implementation(AActor* Actor, const FHorrorEventStruct& Required)
{
	MulticastRPC_CallHorrorEvent(Actor, Required);
}

void UHorrorEventCallerComponent::MulticastRPC_CallHorrorEvent_Implementation(AActor* Actor, const FHorrorEventStruct& Required)
{
	if (Actor->GetClass()->ImplementsInterface(UHorrorEventObjectInterface::StaticClass()))
	{
		IHorrorEventObjectInterface::Execute_CallHorrorEvent(Actor, Required);
	}

	// If there is a horror event component, it invokes the horror event.
	UHorrorEventComponent* EventComponent = Cast<UHorrorEventComponent>(Required.Object->GetComponentByClass(UHorrorEventComponent::StaticClass()));
	if (EventComponent)
	{
		EventComponent->ExecuteHorrorEvent(Required);
	}
}

