// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorPlaneMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <Engine/World.h>
#include "DrawDebugHelpers.h"

void UHorrorPlaneMoveableComponent::PrepareMoving_Implementation(const FHitResult& HitLocation)
{
	check(HitLocation.TraceEnd.Equals(HitLocation.TraceStart) == false);

	const FVector& Direction = (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal();
	LastIntersectionLocation = GetComponentLocation();

	const FVector& FirstIntersectionLocation = IHorrorMoveableInterface::Execute_GetIntersectionPoint(this, HitLocation.TraceStart, Direction);
	UpdateRelativeWithVirtualTransform(IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, FirstIntersectionLocation));

	LastBlocking = false;
	if (PrepareMovingDelegate.IsBound())
	{
		PrepareMovingDelegate.Broadcast(this);
	}
}

void UHorrorPlaneMoveableComponent::EndMoving_Implementation()
{
	if (EndMovingDelegate.IsBound())
	{
		EndMovingDelegate.Broadcast(this);
	}
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
		if (SceneComponent->ComponentHasTag(FName("NotMovealbe")))
		{
			continue;
		}

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
			break;
		}
	}

	UpdateLastBlocking(HasBlocking);

	if (HasBlocking)
	{
		return;
	}

	if (MoveDelegate.IsBound())
	{
		MoveDelegate.Broadcast(this);
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

FVector UHorrorPlaneMoveableComponent::DropVectorParameter(const FVector& IntersectionVector) const
{
	USceneComponent* ParentComponent = GetAttachParent();

	if (ParentComponent)
	{

		FVector RemainVector = IntersectionVector - ParentComponent->GetComponentLocation();

		if (MaintainX == false)
		{
			const FVector& Forward = ParentComponent->GetForwardVector();
			RemainVector -= (RemainVector | Forward) * Forward;
		}

		if (MaintainY == false)
		{
			const FVector& Right = ParentComponent->GetRightVector();
			RemainVector -= (RemainVector | Right) * Right;
		}

		return RemainVector + ParentComponent->GetComponentLocation();
	}
	else
	{
		return FVector(
			MaintainX ? IntersectionVector.X : 0.f,
			MaintainY ? IntersectionVector.Y : 0.f,
			IntersectionVector.Z
		);
	}
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
	const FVector& RemainVector = DropVectorParameter(NewDestinationTransfrom.GetLocation());
	DestinationTransfrom = FTransform(NewDestinationTransfrom.GetRotation(), RemainVector, NewDestinationTransfrom.GetScale3D());
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

void UHorrorPlaneMoveableComponent::UpdateLastBlocking(bool NewHasBlocking)
{
	if (LastBlocking && !NewHasBlocking)
	{
		if (BlockMovingDelegate.IsBound())
		{
			BlockMovingDelegate.Broadcast(this);
		}
	}

	if (LastBlocking != NewHasBlocking)
	{
		LastBlocking = NewHasBlocking;
	}
}
