// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventCallerComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "HorrorEventComponent.h"

void UHorrorEventCallerComponent::CallHorrorEvent(const FVector& Origin, const FVector& Direction)
{
	FHitResult HitResult;
	TraceEventComponent(Origin, Direction, HitResult);

	if (!HitResult.Actor.IsValid())
	{
		return;
	}

	FHorrorEventStruct Required(this, nullptr, Origin, Direction);

	TArray<UHorrorEventComponent*> Components;
	HitResult.Actor->GetComponents<UHorrorEventComponent>(Components);
	for (UHorrorEventComponent* Component : Components)
	{
		Required.Object = Component;

		Component->ExecuteHorrorEvent(Required);
	}

	ServerRPC_MulticastHorrorEvent(Required);
}

void UHorrorEventCallerComponent::TraceEventComponent(const FVector& Origin, const FVector& Direction, FHitResult& HitResult)
{
#if !NO_CVARS
	static const auto DebugDrawEventCall = IConsoleManager::Get().FindConsoleVariable(TEXT("Horror.DebugDrawEventCall"));
#endif

	TArray<AActor*> IgnoreActors;
	if (GetOwner())
	{
		IgnoreActors.Add(GetOwner());
	}

	UKismetSystemLibrary::SphereTraceSingle(this, Origin, Origin + Direction * TraceEventLength, TraceRadius, TraceChannel, TraceComplex, IgnoreActors,
#if !NO_CVARS
	(DebugDrawEventCall->GetBool() ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None),
#else
		EDrawDebugTrace::None,
#endif
		HitResult, false
	);
}

bool UHorrorEventCallerComponent::ServerRPC_MulticastHorrorEvent_Validate(const FHorrorEventStruct& Required)
{
	return (Required.Subject != nullptr) && (Required.Object != nullptr);
}

void UHorrorEventCallerComponent::ServerRPC_MulticastHorrorEvent_Implementation(const FHorrorEventStruct& Required)
{
	MulticastRPC_CallHorrorEvent(Required);
}

void UHorrorEventCallerComponent::MulticastRPC_CallHorrorEvent_Implementation(const FHorrorEventStruct& Required)
{
	Required.Object->ExecuteHorrorEvent(Required);
}

