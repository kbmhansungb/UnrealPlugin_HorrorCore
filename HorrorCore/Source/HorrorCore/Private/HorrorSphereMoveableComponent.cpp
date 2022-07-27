// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorSphereMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Engine.h"

#include "DrawDebugHelpers.h"

void UHorrorAxisRotationComponent::PreMoveable() 
{
}

void UHorrorAxisRotationComponent::PostMoveable() 
{
}

FVector UHorrorAxisRotationComponent::GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const
{
	FVector Result;
	FMath::SphereDistToLine(GetComponentLocation(), SphereRadius, Origin, Direction, Result);

	return Result;
}

void UHorrorAxisRotationComponent::SetFirstIntersectionPoint(const FHitResult& HitLocation)
{
	SphereRadius = (HitLocation.Location - GetComponentLocation()).Size();
	FirstIntersectionPoint = GetIntersectionPoint(HitLocation.TraceStart, (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal());
	OriginalRelativeTransform = GetRelativeTransform();
}

void UHorrorAxisRotationComponent::ApplyMoving(const FVector& IntersectionLocation)
{
	FTransform NewRelativeTransform = GetNewVirtualTransform(IntersectionLocation);
	//NewRelativeTransform = ClampNewRelativeTransform(NewRelativeTransform);
	//NewRelativeTransform = AdjustNewRelativeTransform(NewRelativeTransform);

	SetRelativeTransform(NewRelativeTransform);
}

FTransform UHorrorAxisRotationComponent::GetNewVirtualTransform(const FVector& IntersectionLocation) const
{
	const FVector& VO = (FirstIntersectionPoint - GetComponentLocation()).GetSafeNormal();
	const FVector& V1 = (IntersectionLocation - GetComponentLocation()).GetSafeNormal();

	const FVector& Axis = (VO ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | VO);
	const FQuat& Quat = FQuat(Axis, Rad);

	return FTransform(Quat * OriginalRelativeTransform.GetRotation(), OriginalRelativeTransform.GetLocation(), OriginalRelativeTransform.GetScale3D());
}

FTransform UHorrorAxisRotationComponent::ClampNewRelativeTransform(const FTransform& Transform) const
{
	return Transform;
}

FTransform UHorrorAxisRotationComponent::AdjustNewRelativeTransform(const FTransform& Transform) const
{
	return Transform;
}

