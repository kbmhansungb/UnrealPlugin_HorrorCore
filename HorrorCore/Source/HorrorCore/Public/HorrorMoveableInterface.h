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
	UFUNCTION(Category = "Horror|Moveable", BlueprintCallable, BlueprintNativeEvent)
	void PrepareMoving(const FHitResult& HitLocation);
	virtual void PrepareMoving_Implementation(const FHitResult& HitLocation) = 0;

	UFUNCTION(Category = "Horror|Moveable", BlueprintCallable, BlueprintNativeEvent)
	FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const;
	virtual FVector GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const = 0;

	UFUNCTION(Category = "Horror|Moveable", BlueprintCallable, BlueprintNativeEvent)
	void ApplyMoving(const FVector& IntersectionLocation);
	virtual void ApplyMoving_Implementation(const FVector& IntersectionLocation) = 0;

	UFUNCTION(Category = "Horror|Moveable", BlueprintCallable, BlueprintNativeEvent)
	FTransform GetNewVirtualTransform(const FVector& IntersectionLocation) const;
	virtual FTransform GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const = 0;
};
