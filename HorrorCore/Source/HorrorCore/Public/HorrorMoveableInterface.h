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
	virtual void PostMoveable() {}

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const = 0;
	virtual void ApplyMoving(const FVector& IntersectionLocation) = 0;

	virtual FTransform GetNewRelativeTransform(const FVector& IntersectionLocation) const = 0;
	virtual FTransform ClampNewRelativeTransform(const FTransform& Transform) const = 0;
	virtual FTransform AdjustNewRelativeTransform(const FTransform& Transform) const = 0;

};
