// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorSphereMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Engine.h"

#include "DrawDebugHelpers.h"

//void UHorrorSphereMoveableComponent::PreMoveable() 
//{
//}
//
//void UHorrorSphereMoveableComponent::PostMoveable() 
//{
//}

void UHorrorSphereMoveableComponent::PrepareMoving_Implementation(const FHitResult& HitLocation)
{
	SphereRadius = (HitLocation.Location - GetComponentLocation()).Size();
	FirstIntersectionLocation = (GetIntersectionPoint(HitLocation.TraceStart, (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal()));
	OriginalRelativeTransform = GetRelativeTransform();
}

FVector UHorrorSphereMoveableComponent::GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const
{
	FVector Result;
	FMath::SphereDistToLine(GetComponentLocation(), SphereRadius, Origin, Direction, Result);

	return Result;
}

void UHorrorSphereMoveableComponent::ApplyMoving_Implementation(const FVector& IntersectionLocation)
{
	FTransform NewRelativeTransform = GetNewVirtualTransform(IntersectionLocation);
	//NewRelativeTransform = ClampNewRelativeTransform(NewRelativeTransform);
	//NewRelativeTransform = AdjustNewRelativeTransform(NewRelativeTransform);

	SetRelativeTransform(NewRelativeTransform);
}

FTransform UHorrorSphereMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
	const FVector& VO = (FirstIntersectionLocation - GetComponentLocation()).GetSafeNormal();
	const FVector& V1 = (IntersectionLocation - GetComponentLocation()).GetSafeNormal();

	const FVector& Axis = (VO ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | VO);
	const FQuat& Quat = FQuat(Axis, Rad);

	return FTransform(Quat * OriginalRelativeTransform.GetRotation(), OriginalRelativeTransform.GetLocation(), OriginalRelativeTransform.GetScale3D());
}
//
//FTransform UHorrorSphereMoveableComponent::ClampNewRelativeTransform(const FTransform& Transform) const
//{
//	return Transform;
//}
//
//FTransform UHorrorSphereMoveableComponent::AdjustNewRelativeTransform(const FTransform& Transform) const
//{
//	return Transform;
//}

