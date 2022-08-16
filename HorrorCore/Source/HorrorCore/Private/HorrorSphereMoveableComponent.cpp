// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorSphereMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Engine.h"

#include "DrawDebugHelpers.h"

void UHorrorSphereMoveableComponent::PrepareMoving_Implementation(const FHitResult& HitLocation)
{
	SphereRadius = (HitLocation.Location - GetComponentLocation()).Size();
	const FVector& FirstIntersectionLocation = IHorrorMoveableInterface::Execute_GetIntersectionPoint(this, HitLocation.TraceStart, (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal());
	LastNormalizedVector = (FirstIntersectionLocation - GetComponentLocation()) / SphereRadius;

	OriginalRelativeTransform = GetRelativeTransform();

	RelativeWithVirtualTransform = GetComponentTransform();
}

FVector UHorrorSphereMoveableComponent::GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const
{
	check(Direction.IsNormalized());

	FVector ClosetPoint;
	FMath::SphereDistToLine(GetComponentLocation(), SphereRadius, Origin, Direction, ClosetPoint);
	return ClosetPoint;
}

void UHorrorSphereMoveableComponent::ApplyMoving_Implementation(const FVector& IntersectionLocation)
{
	UWorld* World = GetWorld();
	check(World);

	FTransform NewRelativeTransform = IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, IntersectionLocation);
	SetRelativeTransform(NewRelativeTransform);


}

FTransform UHorrorSphereMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
	const FVector& VO = LastNormalizedVector;
	const FVector& V1 = (IntersectionLocation - GetComponentLocation()).GetSafeNormal();

	const FVector& Axis = (VO ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | VO);
	const FQuat& Quat = FQuat(Axis, Rad);

	return FTransform(Quat * OriginalRelativeTransform.GetRotation(), OriginalRelativeTransform.GetLocation(), OriginalRelativeTransform.GetScale3D());
}

