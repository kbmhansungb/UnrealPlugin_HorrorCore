// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/EngineTypes.h"
#include "HorrorMoveableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHorrorMoveableInterface : public UInterface
{
	GENERATED_BODY()
};

class HORRORCORE_API IHorrorMoveableInterface
{
	GENERATED_BODY()

public:
	//virtual void PreAxisMoveable(const FHitResult& HitResult) = 0;
	//virtual void PostAxisMoveable() = 0;

	//virtual void ApplyAxisMovealbe(USceneComponent* Target, const FVector2D& MouseInput) = 0;
	//
	//virtual void ApplyAxisMoveable(const FVector& Origin, const FVector& Direction) {}

	//virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const { return FVector(); }

	//virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint) const { return FTransform(); }
	//virtual FTransform ClampTransform(const FTransform& Transform) const { return FTransform(); }
	//virtual FTransform AdjustTransform(const FTransform& Transform) const { return FTransform(); }
};
