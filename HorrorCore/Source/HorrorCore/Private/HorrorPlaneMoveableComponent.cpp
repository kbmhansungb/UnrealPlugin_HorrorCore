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
	FirstIntersectionLocation = IHorrorMoveableInterface::Execute_GetIntersectionPoint(this, HitLocation.TraceStart, Direction);

	OriginalRelativeTransform = GetRelativeTransform();
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
	LastIntersectionLocation = IntersectionLocation;
	FTransform ResultRelativeTransform = IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, IntersectionLocation);

	SetRelativeTransform(ResultRelativeTransform);
}

FTransform UHorrorPlaneMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
	FVector NewLocation = OriginalRelativeTransform.GetLocation();
	FVector Deleta = IntersectionLocation - FirstIntersectionLocation;

	Deleta = GetComponentRotation().UnrotateVector(Deleta);

	NewLocation.X += Deleta.X;
	NewLocation.Y += Deleta.Y;

	return FTransform(OriginalRelativeTransform.GetRotation(), NewLocation, OriginalRelativeTransform.GetScale3D());
}

bool UHorrorPlaneMoveableComponent::IsValidDirection(const FVector& Direction) const
{
	return FMath::Abs(FVector::DotProduct(Direction, GetUpVector())) > AllowIntersectionRadian;
}