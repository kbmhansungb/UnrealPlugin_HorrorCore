// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorPlaneMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <Engine/World.h>
#include "DrawDebugHelpers.h"

// IHorrorAxisMoveableInterface에서 상속됨

void UHorrorPlaneMoveableComponent::PrepareMoving_Implementation(const FHitResult& HitLocation)
{
	const FVector& Direction = (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal();
	LastIntersectionLocation = GetComponentLocation();

	OriginalRelativeTransform = GetRelativeTransform();
	const FVector& FirstIntersectionLocation = IHorrorMoveableInterface::Execute_GetIntersectionPoint(this, HitLocation.TraceStart, Direction);
	UpdateVirtualRelativeTransform(IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, FirstIntersectionLocation), GetRelativeTransform());
}

FVector UHorrorPlaneMoveableComponent::GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const
{
	if (IsValidDirection(Direction))
	{
		return FMath::RayPlaneIntersection(Origin, Direction, FPlane(GetComponentLocation(), GetUpVector()));
	}
	else
	{
		return LastIntersectionLocation;
	}
}


void UHorrorPlaneMoveableComponent::ApplyMoving_Implementation(const FVector& IntersectionLocation)
{
	UWorld* World = GetWorld();
	check(World);

	const FTransform& NewRelativeTransform = IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, IntersectionLocation) * VirtualToRelativeTransform;
	SetDestination(NewRelativeTransform);
	const FTransform& NewStepTransform = GetStepToDestination(World->GetDeltaSeconds());
	LastIntersectionLocation = IntersectionLocation;

	const FTransform& Start = GetComponentTransform();
	const FTransform& End = GetComponentTransformFromNewRelative(NewStepTransform);

	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	bool HasBlocking = false;
	for (USceneComponent* SceneComponent : Children)
	{
		TArray<FHitResult> HitResults;

		if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent))
		{
			// Descendant Sweep Test
			FComponentQueryParams QueryParams(SCENE_QUERY_STAT(SweepComponent), GetOwner());

			FTransform PrimitiveWorldTransform = PrimitiveComponent->GetComponentTransform().GetRelativeTransform(Start) * End;

			HasBlocking = World->ComponentSweepMulti(
				HitResults, PrimitiveComponent, 
				PrimitiveComponent->GetComponentLocation(), PrimitiveWorldTransform.GetLocation(), PrimitiveWorldTransform.Rotator(),
				QueryParams);
		}

		if (HasBlocking)
		{
			// 충돌이 있는 경우 움직이지 않습니다.
			return;
		}


	}

	SetRelativeTransform(NewStepTransform);
}

FTransform UHorrorPlaneMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
	const FVector& NewLocation
	{
		IntersectionLocation.X,
		IntersectionLocation.Y,
		OriginalRelativeTransform.GetLocation().Z
	};

	return FTransform(
		GetRelativeRotation(),
		NewLocation, 
		GetRelativeScale3D());
}

bool UHorrorPlaneMoveableComponent::IsValidDirection(const FVector& Direction) const
{
	return FMath::Abs(FVector::DotProduct(Direction, GetUpVector())) > AllowIntersectionRadian;
}

void UHorrorPlaneMoveableComponent::UpdateVirtualRelativeTransform(const FTransform& VirtualTransform, const FTransform& RelativeTransform)
{
	VirtualToRelativeTransform = VirtualTransform.Inverse() * RelativeTransform;
}

FTransform UHorrorPlaneMoveableComponent::GetComponentTransformFromNewRelative(const FTransform& NewRelativeTransform) const
{
	FTransform WorldTransform = NewRelativeTransform;
	if (GetAttachParent())
	{
		WorldTransform *= GetAttachParent()->GetComponentTransform();
	}
	return WorldTransform;
}

void UHorrorPlaneMoveableComponent::SetDestination(const FTransform& NewDestinationRelativeTransfrom)
{
	DestinationRelativeTransfrom = NewDestinationRelativeTransfrom;
}

FTransform UHorrorPlaneMoveableComponent::GetStepToDestination(const float DeletaTime) const
{
	// Destination은 RelativeTransform입니다.

	// 회전이 없으므로 좌표만 생각합니다.
	const FVector& ToDestinationVector = DestinationRelativeTransfrom.GetLocation() - GetRelativeLocation();
	const float Distance = ToDestinationVector.Size();

	if (FLT_EPSILON > Distance)
	{
		return DestinationRelativeTransfrom;
	}

	float MovementScale = MaxStepLength * DeletaTime;
	const FVector& Step = (Distance > MovementScale) ? ToDestinationVector * (MovementScale / Distance) : ToDestinationVector;
	return FTransform(
		GetRelativeRotation(),
		GetRelativeLocation() + Step,
		GetRelativeScale3D()
	);
}
