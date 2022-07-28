// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorPlaneMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <Engine/World.h>
#include "DrawDebugHelpers.h"

// IHorrorAxisMoveableInterface에서 상속됨

void UHorrorPlaneMoveableComponent::PreMoveable()
{
}

void UHorrorPlaneMoveableComponent::PostMoveable()
{
}

FVector UHorrorPlaneMoveableComponent::GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const
{
	return FMath::RayPlaneIntersection(Origin, Direction, FPlane(GetComponentLocation(), GetUpVector()));
}

void UHorrorPlaneMoveableComponent::SetFirstIntersectionPoint(const FHitResult& HitLocation)
{
	const FVector& FirstIntersectionPoint = GetIntersectionPoint(HitLocation.TraceStart, (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal());
	const FTransform& NewVirtualTransform = GetNewVirtualTransform(FirstIntersectionPoint);

	// RT = RT` * VT
	VirtualRelativeTransform = UKismetMathLibrary::MakeRelativeTransform(GetRelativeTransform(), NewVirtualTransform);
}

void UHorrorPlaneMoveableComponent::ApplyMoving(const FVector& IntersectionLocation)
{
	// RT = RT` * V
	FTransform ResultRelativeTransform = VirtualRelativeTransform * GetNewVirtualTransform(IntersectionLocation);

	ResultRelativeTransform = ClampNewRelativeTransform(ResultRelativeTransform);
	ResultRelativeTransform = AdjustNewRelativeTransform(ResultRelativeTransform);
	
	SetRelativeTransform(ResultRelativeTransform);
}

FTransform UHorrorPlaneMoveableComponent::GetNewVirtualTransform(const FVector& IntersectionLocation) const
{
	// W = R * PW
	// W = R` * V * PW

	// V = VT * VR * VS * v
	// VR = VS = I
	// V = VT * v

	// W = R` * VT * PW

	return FTransform(IntersectionLocation);
}

FTransform UHorrorPlaneMoveableComponent::ClampNewRelativeTransform(const FTransform& Transform) const
{
	const FQuat& Quat = Transform.GetRotation();
	const FVector& Scale = Transform.GetScale3D();
	FVector Location = Transform.GetLocation();
	Location.X = FMath::Clamp(Location.X, XRange.X, XRange.Y);
	Location.Y = FMath::Clamp(Location.Y, XRange.X, XRange.Y);
	Location.Z = 0.0f;

	return FTransform( Quat, Location, Scale );
}

FTransform UHorrorPlaneMoveableComponent::AdjustNewRelativeTransform(const FTransform& Transform) const
{
	//TArray<FHitResult> OutHits;

	//FComponentQueryParams Params(SCENE_QUERY_STAT(MoveComponent), GetOwner());
	//FCollisionResponseParams ResponseParam;
	//InitSweepCollisionParams(Params, ResponseParam);
	AActor
	//const UPrimitiveComponent* Primitive = this;
	if (GetWorld()->ComponentSweepMulti(OutHits, const_cast<UPrimitiveComponent*>(Primitive), GetComponentLocation(), Transform.GetLocation(), Transform.GetRotation(), Params))
	//{
	//	int a = 3;
	//}
	
	//const FQuat& Quat = Transform.GetRotation();
	//const FVector& Scale = Transform.GetScale3D();
	//FVector Location = Transform.GetLocation();

	//for (const auto& Hit : OutHits)
	//{
	//	Location -= Hit.ImpactNormal * Hit.Distance;
	//}

	//return FTransform(Quat, Location, Scale);

	return Transform;
}

