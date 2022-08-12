// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "HorrorMoveableInterface.h"
#include "HorrorPlaneMoveableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorPlaneMoveableComponent : public UPrimitiveComponent,
	public IHorrorMoveableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D XRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D YRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStepSize = 10.0f;

	// IHorrorAxisMoveableInterface에서 상속됨
public:
	//virtual void PreMoveable() override;
	//virtual void PostMoveable() override;
	virtual void PrepareMoving_Implementation(const FHitResult& HitLocation) override;
	virtual FVector GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const override;
	virtual void ApplyMoving_Implementation(const FVector& IntersectionLocation) override;
	virtual FTransform GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const override;
	//virtual FTransform ClampNewRelativeTransform(const FTransform& Transform) const override;
	//virtual FTransform AdjustNewRelativeTransform(const FTransform& Transform) const override;

private:
	FVector FirstIntersectionLocation;
	FTransform OriginalRelativeTransform;
};
