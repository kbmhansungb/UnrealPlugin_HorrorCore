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
	check((HitLocation.TraceEnd - HitLocation.TraceStart).Size() > FLT_EPSILON);

	SphereRadius = (HitLocation.Location - GetComponentLocation()).Size();

	const FVector& FirstIntersectionLocation = IHorrorMoveableInterface::Execute_GetIntersectionPoint(this, HitLocation.TraceStart, (HitLocation.TraceEnd - HitLocation.TraceStart).GetUnsafeNormal());
	const FVector& ToIntersectionVector = (FirstIntersectionLocation - GetComponentLocation()) / SphereRadius;
	// Intersection to Upvector
	{
		const FVector& Axis = (ToIntersectionVector ^ GetUpVector()).GetSafeNormal();
		const float& Rad = FMath::Acos(ToIntersectionVector | GetUpVector());

		IntersectionCorrectionQuarts = FQuat(Axis, Rad);
	}

	LastBlocking = false;
	if (PrepareMovingDelegate.IsBound())
	{
		PrepareMovingDelegate.Broadcast(this);
	}
}

void UHorrorSphereMoveableComponent::EndMoving_Implementation()
{
	if (EndMovingDelegate.IsBound())
	{
		EndMovingDelegate.Broadcast(this);
	}
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
		if (SceneComponent->ComponentHasTag(FName("NotMovealbe")))
		{
			continue; 
		}
		
		TArray<FHitResult> HitResults;

		if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent))
		{
			// Descendant Sweep Test
			const FComponentQueryParams QueryParams(SCENE_QUERY_STAT(SweepComponent), GetOwner());
			const FTransform& GoPrimitiveWorldTransform = PrimitiveComponent->GetComponentTransform().GetRelativeTransform(Start) * End;

			// Sweep 검사에서, 회전이 포함되지 않으므로, 갈 수는 있지만, 돌아오지 못하는 상황이 있습니다.
			// 따라서 돌아올 수 있는지 확인하여, 이동을 결정하는 것은 어느정도는... 그럴싸하게 작동합니다.

			const bool SweepHitWhenGoing = World->ComponentSweepMulti(
				HitResults, PrimitiveComponent,
				PrimitiveComponent->GetComponentLocation(), GoPrimitiveWorldTransform.GetLocation(), GoPrimitiveWorldTransform.Rotator(),
				QueryParams);

			TArray<FHitResult> ComeHitResults;
			const bool SweepHitWhenComming = World->ComponentSweepMulti(
				ComeHitResults, PrimitiveComponent,
				GoPrimitiveWorldTransform.GetLocation(), PrimitiveComponent->GetComponentLocation(), PrimitiveComponent->GetComponentRotation(),
				QueryParams);

			HasBlocking = SweepHitWhenGoing || SweepHitWhenComming;
		}

		if (HasBlocking)
		{
			break;
		}
	}

	UpdateLastBlocking(HasBlocking);

	if (HasBlocking)
	{
		return;
	}

	if (MoveDelegate.IsBound())
	{
		MoveDelegate.Broadcast(this);
	}

	SetWorldTransform(NewVirtualTransform);
}

FTransform UHorrorSphereMoveableComponent::GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const
{
	const FVector& V0 = GetUpVector();
	FVector V1 = IntersectionCorrectionQuarts.RotateVector(IntersectionLocation - GetComponentLocation());
	V1 = DropVectorParameter(V1);
	V1.Normalize();

	V1 = StepToDestination(V0, V1);

	const FVector& Axis = (V0 ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | V0);
	LastRotRad = Rad;

	const FQuat& Quat = FQuat(Axis, Rad);

	return FTransform(Quat * GetComponentQuat(), GetComponentLocation(), GetComponentScale());
}

float UHorrorSphereMoveableComponent::GetLastRotRad() const
{
	return LastBlocking ? 0.f : LastRotRad;
}

FVector UHorrorSphereMoveableComponent::DropVectorParameter(const FVector& SphereVector) const
{
	USceneComponent* ParentComponent = GetAttachParent();

	FVector RemainVector = SphereVector;
	if (ParentComponent)
	{
		if (MaintainX == false)
		{
			const FVector& Forward = ParentComponent->GetForwardVector();
			RemainVector -= (SphereVector | Forward) * Forward;
		}

		if (MaintainY == false)
		{
			const FVector& Right = ParentComponent->GetRightVector();
			RemainVector -= (SphereVector | Right) * Right;
		}

		if (MaintainZ == false)
		{
			const FVector& Up = ParentComponent->GetUpVector();
			RemainVector -= (SphereVector | Up) * Up;
		}
	}
	else
	{
		RemainVector = FVector(
			MaintainX ? SphereVector.X : 0.f,
			MaintainY ? SphereVector.Y : 0.f,
			MaintainZ ? SphereVector.Z : 0.f
		);
	}

	return RemainVector;
}

void UHorrorSphereMoveableComponent::UpdateLastBlocking(bool NewHasBlocking)
{
	if (!LastBlocking && NewHasBlocking)
	{
		if (BlockMovingDelegate.IsBound())
		{
			BlockMovingDelegate.Broadcast(this);
		}
	}

	if (LastBlocking != NewHasBlocking)
	{
		LastBlocking = NewHasBlocking;
	}
}

FVector UHorrorSphereMoveableComponent::StepToDestination(const FVector& Current, const FVector& Destination) const
{
	const float& Omega = FMath::Acos(Current | Destination);
	const float& MaxAllowedOmega = FMath::DegreesToRadians(MaxRotationSpeed * GetWorld()->GetDeltaSeconds());

	if (Omega > MaxAllowedOmega)
	{
		// 전체 Omega에서 허용되는 Omega만큼만 이동합니다.
		const float& LerpScale = MaxAllowedOmega / Omega;
		return SLerpVector(Current, Destination, LerpScale, Omega);
	}
	return Current;
}

FVector UHorrorSphereMoveableComponent::SLerpVector(const FVector& CurrentVector, const FVector& DesiredVector, const float LerpScale, const float Omega) const
{
	// https://en.wikipedia.org/wiki/Slerp#:~:text=More%20familiar%20than%20the%20general,this%20becomes%20the%20Slerp%20formula.

	const float& ASinRad = FMath::Sin((1 - LerpScale) * Omega);
	const float& BSinRad = FMath::Sin(LerpScale * Omega);
	const float& SinRad = FMath::Sin(Omega);

	return (ASinRad / SinRad) * CurrentVector + (BSinRad / SinRad) * DesiredVector;
}

