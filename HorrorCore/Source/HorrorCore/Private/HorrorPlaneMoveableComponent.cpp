// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorPlaneMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"

// IHorrorAxisMoveableInterface에서 상속됨

void UHorrorAxisMovementComponent::PreMoveable()
{
}

void UHorrorAxisMovementComponent::PostMoveable()
{
}

FVector UHorrorAxisMovementComponent::GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const
{
	return FMath::RayPlaneIntersection(Origin, Direction, FPlane(GetComponentLocation(), GetUpVector()));
}

// FHitResult.TraceStart와 FHitResult.TraceEnd는 서로 달라야 합니다.

void UHorrorAxisMovementComponent::SetFirstIntersectionPoint(const FHitResult& HitLocation)
{
	const FVector& FirstIntersectionPoint = GetIntersectionPoint(HitLocation.TraceStart, (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal());
	const FTransform& NewVirtualTransform = GetNewVirtualTransform(FirstIntersectionPoint);

	// RT = RT` * VT
	VirtualRelativeTransform = UKismetMathLibrary::MakeRelativeTransform(GetRelativeTransform(), NewVirtualTransform);
}

void UHorrorAxisMovementComponent::ApplyMoving(const FVector& IntersectionLocation)
{
	// RT = RT` * V
	FTransform ResultRelativeTransform = VirtualRelativeTransform * GetNewVirtualTransform(IntersectionLocation);

	SetRelativeTransform(ResultRelativeTransform);
}

// FHitResult.TraceStart와 FHitResult.TraceEnd는 서로 달라야 합니다.

