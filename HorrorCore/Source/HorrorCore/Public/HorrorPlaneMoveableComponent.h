// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "HorrorMoveableInterface.h"
#include "HorrorPlaneMoveableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorAxisMovementComponent : public UPrimitiveComponent,
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
	virtual void PreMoveable() override;
	virtual void PostMoveable() override;

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override;
	// FHitResult.TraceStart와 FHitResult.TraceEnd는 서로 달라야 합니다.
	virtual void SetFirstIntersectionPoint(const FHitResult& HitLocation) override;
	virtual void ApplyMoving(const FVector& IntersectionLocation) override;

	virtual FTransform GetNewVirtualTransform(const FVector& IntersectionLocation) const override 
	{ 
		return FTransform(); 
	}
	virtual FTransform ClampNewRelativeTransform(const FTransform& Transform) const override;
	virtual FTransform AdjustNewRelativeTransform(const FTransform& Transform) const override;

private:
	FTransform VirtualRelativeTransform;
};
