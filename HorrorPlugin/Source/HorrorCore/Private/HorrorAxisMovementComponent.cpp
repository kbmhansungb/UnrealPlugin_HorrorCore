// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorAxisMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"

// IHorrorAxisMoveableInterface에서 상속됨

UHorrorAxisMovementComponent::UHorrorAxisMovementComponent()
{
}

void UHorrorAxisMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHorrorAxisMovementComponent::PreAxisMoveable(const FHitResult& HitResult)
{
	FirsColsestPoint = GetIntersectionPoint(HitResult.TraceStart, (HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal());
}

void UHorrorAxisMovementComponent::ApplyAxisMoveable(const FVector& Origin, const FVector& Direction)
{
	const FVector& OutClosestPoint = GetIntersectionPoint(Origin, Direction);
	SetRelativeTransform(GetNewReleativeTransform(OutClosestPoint));
}

FVector UHorrorAxisMovementComponent::GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const
{
	return FMath::RayPlaneIntersection(Origin, Direction, FPlane(GetComponentLocation(), GetUpVector()));
}

FTransform UHorrorAxisMovementComponent::GetNewReleativeTransform(const FVector& OutClosestPoint) const
{
	FTransform Transform;
	Transform = AdjustTransform(Transform);
	Transform = ClampTransform(Transform);
	return Transform;
}

FTransform UHorrorAxisMovementComponent::ClampTransform(const FTransform& Transform) const
{
	const FVector& Loc = Transform.GetLocation();
	FVector Location = FVector(
		FMath::Clamp(Loc.X, XRange.X, XRange.Y),
		FMath::Clamp(Loc.Y, YRange.X, YRange.Y),
		Loc.Z
	);
	return FTransform(Transform.GetRotation(), Loc, Transform.GetScale3D());
}

FTransform UHorrorAxisMovementComponent::AdjustTransform(const FTransform& Transform) const
{
	return Transform;
}
