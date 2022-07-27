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


	// IHorrorAxisMoveableInterface에서 상속됨
protected:
	virtual void PreMoveable() override;
	virtual void PostMoveable() override;

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override;
	// FHitResult.TraceStart와 FHitResult.TraceEnd는 서로 달라야 합니다.
	virtual void SetFirstIntersectionPoint(const FHitResult& HitLocation) override;
	virtual void ApplyMoving(const FVector& IntersectionLocation) override;

	virtual FTransform GetNewVirtualTransform(const FVector& IntersectionLocation) const override;
	virtual FTransform ClampNewRelativeTransform(const FTransform& Transform) const override
	{
		return Transform;
	}
	virtual FTransform AdjustNewRelativeTransform(const FTransform& Transform) const override;

private:
	float SphereRadius;
	FVector FirstIntersectionPoint;
	FTransform OriginalRelativeTransform;

	//virtual void ApplyAxisMoveable(const FVector& Origin, const FVector& Direction) override
	//{
	//	const FVector& OutClosestPoint = GetIntersectionPoint(Origin, Direction);
	//	SetRelativeTransform(GetNewReleativeTransform(OutClosestPoint));
	//}
	//virtual FTransform ClampTransform(const FTransform& Transform) const override
	//{
	//	if (!GetAttachParent())
	//	{
	//		return Transform;
	//	}
	//	const FVector& Axis = GetAttachParent()->GetUpVector();

	//	FQuat Swing, Twist;
	//	Transform.GetRotation().ToSwingTwist(Axis, Swing, Twist);

	//	float TwistAngle = FMath::RadiansToDegrees((Twist.Z > 0.f) ? Twist.GetAngle() : -Twist.GetAngle());
	//	TwistAngle = FMath::Clamp(TwistAngle, TwistLimit.X, TwistLimit.Y);

	//	const FQuat& LimitedTwist = FQuat(Axis, FMath::DegreesToRadians(TwistAngle));

	//	DrawDebugLine(GetWorld(), GetComponentLocation(), GetComponentLocation() + Axis * (SphereRadius + 10.0f), FColor::Blue);
	//	UE_LOG(LogTemp, Display, TEXT("Twist : %s, Angle : %f, Limited Twist : %s"), *Twist.ToString(), TwistAngle, *LimitedTwist.ToString());


	//	return FTransform(LimitedTwist * Swing, Transform.GetLocation(), Transform.GetScale3D());

	//	//return Transform;
	//}
};
