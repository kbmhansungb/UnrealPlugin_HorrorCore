// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventFunctionLibrary.h"
#include "HorrorEventComponent.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

#define DRAWING_PARAM false, 1.0f

void UHorrorEventFunctionLibrary::GetHorrorEventComponent(AActor* Actor, const FVector& Start, const FVector& Direction, float Length, UHorrorEventComponent*& HorrorEventComponent)
{
	HorrorEventComponent = nullptr;

	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Actor);
	if (Actor->GetWorld()->LineTraceSingleByObjectType(HitResult, Start, Start + Direction * Length, ObjectQueryParams, QueryParams))
	{
		if (!HitResult.Actor.IsValid())
		{
			return;
		}

		HorrorEventComponent = Cast<UHorrorEventComponent>(HitResult.Actor->GetComponentByClass(UHorrorEventComponent::StaticClass()));

#if ENABLE_DRAW_DEBUG

		DrawDebugLine(Actor->GetWorld(), HitResult.TraceStart, HitResult.Location, FColor::Green, DRAWING_PARAM);

#endif
	}
}

void UHorrorEventFunctionLibrary::GetHorrorEventComponentLikeEye(AActor* Actor, const FVector& Start, const FVector& Direction, float Length, float Radius, UHorrorEventComponent*& HorrorEventComponent)
{
	TArray<FHitResult> HitResults;
	FCollisionObjectQueryParams QueryParams;
	Actor->GetWorld()->SweepMultiByObjectType(HitResults, Start, Start + Direction * Length, FQuat::Identity, QueryParams, FCollisionShape::MakeSphere(Radius));

#if ENABLE_DRAW_DEBUG

	FVector Center = (Start + (Start + Direction * Length)) / 2.0f;
	FVector Axis = Center - Start;
	FQuat Quat = Axis.Normalize() ? FRotationMatrix::MakeFromZ(Axis).ToQuat() : FQuat::Identity;
	DrawDebugCapsule(Actor->GetWorld(), Center, Length / 2.0f, Radius, Quat, FColor::Blue, DRAWING_PARAM);

#endif // ENABLE_DRAW_DEBUG

	struct
	{
		FORCEINLINE bool operator()(const FHitResult& A, const FHitResult& B) const
		{
			return A.Distance < B.Distance;
		}
	} COMPARE_DISTANCE;
	HitResults.Sort(COMPARE_DISTANCE);

	if ( !(HitResults.Num() > 0) )
	{
		return;
	}

	for (const FHitResult& HitResult : HitResults)
	{
		if ( !(FVector::DotProduct(Direction, HitResult.Normal) < 0) )
		{
			continue;
		}
		
		if ( !HitResult.Actor.IsValid() )
		{
			continue;
		}

		HorrorEventComponent = Cast<UHorrorEventComponent>(HitResult.Actor->GetComponentByClass(UHorrorEventComponent::StaticClass()));
		if ( !HorrorEventComponent )
		{
			continue;
		}

#if ENABLE_DRAW_DEBUG

		DrawDebugLine(Actor->GetWorld(), Start, HitResult.Location, FColor::Green, DRAWING_PARAM);

#endif
		return;
	}
}

#undef DRAWING_PARAM