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

	const FTransform NewVirtualTransform = IHorrorMoveableInterface::Execute_GetNewVirtualTransform(this, IntersectionLocation);
	
	const FTransform Start = GetComponentTransform();
	const FTransform End = NewVirtualTransform;

	SetWorldTransform(NewVirtualTransform);
}

FTransform UHorrorSphereMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
#define DEBUG_SPHERE_SIZE 5.0f
#define DEBUG_SPHERE_SEGMENT 16

	const FVector& V0 = GetUpVector();
	FVector V1 = (IntersectionLocation - GetComponentLocation()) / SphereRadius;

	DrawDebugSphere(GetWorld(), V0 * SphereRadius + GetComponentLocation(), DEBUG_SPHERE_SIZE, DEBUG_SPHERE_SEGMENT, FColor::Red);
	DrawDebugSphere(GetWorld(), V1 * SphereRadius + GetComponentLocation(), DEBUG_SPHERE_SIZE, DEBUG_SPHERE_SEGMENT, FColor::Blue);

	{
		const float& Radian = FMath::Acos(V1 | V0);
		const float& MaxRadian = FMath::DegreesToRadians(MaxRotationSpeed * GetWorld()->GetDeltaSeconds());
		
		if (Radian > MaxRadian)
		{
			const float& t = MaxRadian / Radian;

			const float& ASinRad = FMath::Sin((1 - t) * Radian);
			const float& BSinRad = FMath::Sin(t * Radian);
			const float& SinRad = FMath::Sin(Radian);

			V1 = (ASinRad / SinRad) * V0 + (BSinRad / SinRad) * V1;
		}
	}

	DrawDebugSphere(GetWorld(), V1 * SphereRadius + GetComponentLocation(), DEBUG_SPHERE_SIZE, DEBUG_SPHERE_SEGMENT, FColor::Green);

	const FVector& Axis = (V0 ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | V0);

	const FQuat& Quat = FQuat(Axis, Rad);

	return FTransform(Quat * GetComponentQuat(), GetComponentLocation(), GetComponentScale());

#undef DEBUG_SPHERE_SIZE
}

