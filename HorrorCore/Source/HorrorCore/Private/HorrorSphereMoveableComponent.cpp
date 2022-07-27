// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorSphereMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Engine.h"

#include "DrawDebugHelpers.h"

void UHorrorAxisRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	FRay Ray = GetNowMouseRay(PC);
	//ApplyAxisMoveable(Ray.Origin, Ray.Direction);

	if ( Key.IsValid() && !(PC->GetInputAnalogKeyState(Key) > 0.f))
	{
		SetComponentTickEnabled(false);
	}
}

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

FTransform UHorrorAxisRotationComponent::GetNewVirtualTransform(const FVector& IntersectionLocation) const
{
	const FVector& VO = (FirstIntersectionPoint - GetComponentLocation()).GetSafeNormal();
	const FVector& V1 = (IntersectionLocation - GetComponentLocation()).GetSafeNormal();

	const FVector& Axis = (VO ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | VO);
	const FQuat& Quat = FQuat(Axis, Rad);

	return FTransform(Quat * OriginalRelativeTransform.GetRotation(), OriginalRelativeTransform.GetLocation(), OriginalRelativeTransform.GetScale3D());
}

FTransform UHorrorAxisRotationComponent::AdjustNewRelativeTransform(const FTransform& Transform) const
{
	return Transform;
}

