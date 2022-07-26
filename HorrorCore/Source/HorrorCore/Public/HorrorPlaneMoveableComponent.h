// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorMoveableInterface.h"
#include "HorrorPlaneMoveableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorAxisMovementComponent : public USceneComponent,
	public IHorrorMoveableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHorrorAxisMovementComponent();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D XRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D YRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStepSize = 10.0f;

protected:
	//// IHorrorAxisMoveableInterface에서 상속됨
	//virtual void PreAxisMoveable(const FHitResult& HitResult) override
	//{
	//	FirsColsestPoint = GetIntersectionPoint(HitResult.TraceStart, (HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal());
	//}
	//virtual void ApplyAxisMoveable(const FVector& Origin, const FVector& Direction) override
	//{
	//	const FVector& OutClosestPoint = GetIntersectionPoint(Origin, Direction);
	//	SetRelativeTransform(GetNewReleativeTransform(OutClosestPoint));
	//}

	//virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override
	//{
	//	return FMath::RayPlaneIntersection(Origin, Direction, FPlane(GetComponentLocation(), GetUpVector()));
	//}

	//virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint) const override
	//{
	//	FTransform Transform;
	//	Transform = AdjustTransform(Transform);
	//	Transform = ClampTransform(Transform);
	//	return Transform;
	//}
	//virtual FTransform ClampTransform(const FTransform& Transform) const override
	//{
	//	const FVector& Loc = Transform.GetLocation();
	//	FVector Location = FVector(
	//		FMath::Clamp(Loc.X, XRange.X, XRange.Y),
	//		FMath::Clamp(Loc.Y, YRange.X, YRange.Y),
	//		Loc.Z
	//	);
	//	return FTransform(Transform.GetRotation(), Loc, Transform.GetScale3D());
	//}
	//virtual FTransform AdjustTransform(const FTransform& Transform) const override
	//{
	//	return Transform;
	//}

private:
	FVector FirsColsestPoint;
};
