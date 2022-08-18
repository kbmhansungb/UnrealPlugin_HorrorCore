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

	const FVector& FirstIntersectionLocation = IHorrorMoveableInterface::Execute_GetIntersectionPoint(this, HitLocation.TraceStart, Direction);
	UpdateRelativeWithVirtualTransform(IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, FirstIntersectionLocation));
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

	SetDestination(GetNewWorldTransform(IntersectionLocation));
	const FTransform& NewStepTransform = GetStepToDestination(World->GetDeltaSeconds());

	const FTransform& Start = GetComponentTransform();
	const FTransform& End = NewStepTransform;

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

	SetWorldTransform(NewStepTransform);
}

FTransform UHorrorPlaneMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
	const FVector& NewLocation
	{
		IntersectionLocation.X,
		IntersectionLocation.Y,
		GetComponentLocation().Z
	};

	const FTransform& NewVirtualTransform = FTransform(
		GetComponentRotation(),
		NewLocation, 
		GetComponentScale());

	return NewVirtualTransform;
}

bool UHorrorPlaneMoveableComponent::IsValidDirection(const FVector& Direction) const
{
	return FMath::Abs(FVector::DotProduct(Direction, GetUpVector())) > AllowIntersectionRadian;
}

void UHorrorPlaneMoveableComponent::UpdateRelativeWithVirtualTransform(const FTransform& VirtualTransform)
{
	RelativeWithVirtualTransform = GetComponentTransform() * VirtualTransform.Inverse();
}

FTransform UHorrorPlaneMoveableComponent::GetNewWorldTransform(const FVector& IntersectionLocation)
{
	const FTransform& NewRelativeTransform = RelativeWithVirtualTransform * IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, IntersectionLocation);
	LastIntersectionLocation = IntersectionLocation;
	return NewRelativeTransform;
}

void UHorrorPlaneMoveableComponent::SetDestination(const FTransform& NewDestinationTransfrom)
{
	DestinationTransfrom = NewDestinationTransfrom;
}

FTransform UHorrorPlaneMoveableComponent::GetStepToDestination(const float DeletaTime) const
{
	// Destination은 RelativeTransform입니다.

	// 회전이 없으므로 좌표만 생각합니다.
	const FVector& ToDestinationVector = DestinationTransfrom.GetLocation() - GetComponentLocation();
	const float Distance = ToDestinationVector.Size();

	if (FLT_EPSILON > Distance)
	{
		return DestinationTransfrom;
	}

	float MovementScale = MaxStepLength * DeletaTime;
	const FVector& Step = (Distance > MovementScale) ? ToDestinationVector * (MovementScale / Distance) : ToDestinationVector;
	return FTransform(
		GetComponentRotation(),
		GetComponentLocation() + Step,
		GetComponentScale()
	);
}
