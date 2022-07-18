// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/EngineTypes.h"
#include "HorrorAxisMoveableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHorrorAxisMoveableInterface : public UInterface
{
	GENERATED_BODY()
};

class HORRORCORE_API IHorrorAxisMoveableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void ApplyAxisMovealbe(USceneComponent* Target, const FVector2D& MouseInput);
	virtual void ApplyAxisMovealbe_Implementation(USceneComponent* Target, const FVector2D& MouseInput){}
	

	virtual void PreAxisMoveable(const FHitResult& HitResult) {}
	virtual void ApplyAxisMoveable(const FVector& Origin, const FVector& Direction) {}

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const { return FVector(); }

	virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint) const { return FTransform(); }
	virtual FTransform ClampTransform(const FTransform& Transform) const { return FTransform(); }
	virtual FTransform AdjustTransform(const FTransform& Transform) const { return FTransform(); }
};
