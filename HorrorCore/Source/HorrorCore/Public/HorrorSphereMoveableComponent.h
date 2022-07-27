// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorMoveableInterface.h"
#include "InputCoreTypes.h"
#include "HorrorSphereMoveableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorAxisRotationComponent : public USceneComponent,
	public IHorrorMoveableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D SwingLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TwistLimit;

	// IHorrorAxisMoveableInterface에서 상속됨
protected:
	virtual void PreMoveable() override;
	virtual void PostMoveable() override;

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override;
	// FHitResult.TraceStart와 FHitResult.TraceEnd는 서로 달라야 합니다.
	virtual void SetFirstIntersectionPoint(const FHitResult& HitLocation) override;
	virtual void ApplyMoving(const FVector& IntersectionLocation) override;

	virtual FTransform GetNewVirtualTransform(const FVector& IntersectionLocation) const override;
	virtual FTransform ClampNewRelativeTransform(const FTransform& Transform) const override;
	virtual FTransform AdjustNewRelativeTransform(const FTransform& Transform) const override;

private:
	float SphereRadius;
	FVector FirstIntersectionPoint;
	FTransform OriginalRelativeTransform;
};
