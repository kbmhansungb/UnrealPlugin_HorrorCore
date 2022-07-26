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
	virtual void PreMoveable() {}

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direct) const = 0;
	virtual void ApplyMoving(const FVector& IntersectionLocation) = 0;

	virtual void PostMoveable() {}

	//virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint) const { return FTransform(); }
	//virtual FTransform ClampTransform(const FTransform& Transform) const { return FTransform(); }
	//virtual FTransform AdjustTransform(const FTransform& Transform) const { return FTransform(); }
};
