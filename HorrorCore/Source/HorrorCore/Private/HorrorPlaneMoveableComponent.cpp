// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorPlaneMoveableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"

// IHorrorAxisMoveableInterface에서 상속됨

// IHorrorAxisMoveableInterface에서 상속됨

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
