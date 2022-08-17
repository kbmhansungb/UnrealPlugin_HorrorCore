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

	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	bool HasBlocking = false;
	for (USceneComponent* SceneComponent : Children)
	{
		TArray<FHitResult> HitResults;

		if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent))
		{
			// Descendant Sweep Test
			const FComponentQueryParams QueryParams(SCENE_QUERY_STAT(SweepComponent), GetOwner());
			const FTransform& GoPrimitiveWorldTransform = PrimitiveComponent->GetComponentTransform().GetRelativeTransform(Start) * End;

			// Sweep 검사에서, 회전이 포함되지 않으므로, 갈 수는 있지만, 돌아오지 못하는 상황이 있습니다.
			// 따라서 돌아올 수 있는지 확인하여, 이동을 결정하는 것은
			// 완벽한 해결책은 아니지만 그럴싸하게 작동합니다.

			const bool CanGo = World->ComponentSweepMulti(
				HitResults, PrimitiveComponent,
				PrimitiveComponent->GetComponentLocation(), GoPrimitiveWorldTransform.GetLocation(), GoPrimitiveWorldTransform.Rotator(),
				QueryParams);

			TArray<FHitResult> ComeHitResults;
			const bool CanCome = World->ComponentSweepMulti(
				ComeHitResults, PrimitiveComponent,
				GoPrimitiveWorldTransform.GetLocation(), PrimitiveComponent->GetComponentLocation(), PrimitiveComponent->GetComponentRotation(),
				QueryParams);

			HasBlocking = CanGo && CanCome;
		}

		if (HasBlocking)
		{
			return;
		}
	}

	SetWorldTransform(NewVirtualTransform);
}

FTransform UHorrorSphereMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
	static constexpr float DebugSphereSize = 5.0f;
	static constexpr int32 DebugSphereSegment = 16;

	const FVector& V0 = GetUpVector();
	FVector V1 = (IntersectionLocation - GetComponentLocation()) / SphereRadius;

	DrawDebugSphere(GetWorld(), V0 * SphereRadius + GetComponentLocation(), DebugSphereSize, DebugSphereSegment, FColor::Red);
	DrawDebugSphere(GetWorld(), V1 * SphereRadius + GetComponentLocation(), DebugSphereSize, DebugSphereSegment, FColor::Blue);

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

	DrawDebugSphere(GetWorld(), V1 * SphereRadius + GetComponentLocation(), DebugSphereSize, DebugSphereSegment, FColor::Green);

	const FVector& Axis = (V0 ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | V0);

	const FQuat& Quat = FQuat(Axis, Rad);

	return FTransform(Quat * GetComponentQuat(), GetComponentLocation(), GetComponentScale());
}

