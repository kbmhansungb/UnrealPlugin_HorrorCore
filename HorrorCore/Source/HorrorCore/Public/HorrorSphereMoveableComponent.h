// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorMoveableInterface.h"
#include "InputCoreTypes.h"
#include "HorrorSphereMoveableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorSphereMoveableComponent : public USceneComponent,
	public IHorrorMoveableInterface
{
	GENERATED_BODY()

public:

	// IHorrorAxisMoveableInterface에서 상속됨
protected:
	//virtual void PreMoveable() override;
	//virtual void PostMoveable() override;
	virtual void PrepareMoving_Implementation(const FHitResult& HitLocation) override;
	virtual FVector GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const override;
	virtual void ApplyMoving_Implementation(const FVector& IntersectionLocation) override;
	virtual FTransform GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const override;
	//virtual FTransform ClampNewRelativeTransform(const FTransform& Transform) const override;
	//virtual FTransform AdjustNewRelativeTransform(const FTransform& Transform) const override;

private:
	float SphereRadius;
	FVector FirstIntersectionLocation;
	FTransform OriginalRelativeTransform;
};
