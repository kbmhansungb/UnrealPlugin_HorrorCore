// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventCallerComponent.h"
#include "HorrorEventComponent.h"
#include "HorrorEventInstance.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"

void UHorrorEventCallerComponent::CallHorrorEvent(const FVector& Origin, const FVector& Direction)
{
	FHitResult HitResult;
	TraceEventComponent(Origin, Direction, HitResult);

	if (!HitResult.Actor.IsValid())
	{
		return;
	}

	UHorrorEventComponent* EventComponent = Cast<UHorrorEventComponent>(HitResult.Actor->GetComponentByClass(UHorrorEventComponent::StaticClass()));
	if (!EventComponent)
	{
		return;
	}

	FHorrorEventStruct Required(this, EventComponent, Origin, Direction);
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

