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
	UHorrorAxisRotationComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetComponentTickEnabled(bool bEnabled) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Swing1Limit;// = FVector2D(-60.0f, 60.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Swing2Limit;// = FVector2D(-60.0f, 60.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TwistLimit = FVector2D(-10.0f, 10.0f);

	UFUNCTION(BlueprintCallable)
	void ClickedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable)
	void ReleasedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	virtual FRay GetNowMouseRay(APlayerController* PC);
	
protected:
	// IHorrorAxisMoveableInterface에서 상속됨
	virtual void PreMoveable() override {}
	virtual void PostMoveable() override {}

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override { return FVector(); }
	virtual void SetFirstIntersectionPoint(const FHitResult& HitLocation) override {}
	virtual void ApplyMoving(const FVector& IntersectionLocation) override {}

	virtual FTransform GetNewVirtualTransform(const FVector& IntersectionLocation) const override { return FTransform(); }
	virtual FTransform ClampNewRelativeTransform(const FTransform& Transform) const override { return FTransform(); }
	virtual FTransform AdjustNewRelativeTransform(const FTransform& Transform) const override { return FTransform(); }

	//virtual void PreAxisMoveable(const FHitResult& HitResult) override
	//{
	//	SphereRadius = (HitResult.Location - GetComponentLocation()).Size();
	//	FirstClosestPoint = GetIntersectionPoint(HitResult.TraceStart, (HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal());
	//	OriginalRelativeTransform = GetRelativeTransform();
	//}
	//virtual void ApplyAxisMoveable(const FVector& Origin, const FVector& Direction) override
	//{
	//	const FVector& OutClosestPoint = GetIntersectionPoint(Origin, Direction);
	//	SetRelativeTransform(GetNewReleativeTransform(OutClosestPoint));
	//}

	//virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override
	//{
	//	FVector OutClosestPoint;

	//	FMath::SphereDistToLine(GetComponentLocation(), SphereRadius, Origin, Direction, OutClosestPoint);
	//	DrawDebugSphere(GetWorld(), FirstClosestPoint, 5.0f, 16, FColor::Blue);
	//	DrawDebugSphere(GetWorld(), OutClosestPoint, 5.0f, 16, FColor::Green);

	//	return OutClosestPoint;
	//}

	//virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint) const override
	//{
	//	const FVector& VO = FirstClosestPoint.GetSafeNormal();
	//	const FVector& V1 = (OutClosestPoint - GetComponentLocation()).GetSafeNormal();

	//	// 개선할 수 있음.
	//	const FVector& Axis = (VO ^ V1).GetSafeNormal();
	//	const float& Rad = FMath::Acos(V1 | VO);
	//	const FQuat& Quat = FQuat(Axis, Rad);

	//	FTransform NewTransform = FTransform(Quat * OriginalRelativeTransform.GetRotation(), OriginalRelativeTransform.GetLocation(), OriginalRelativeTransform.GetScale3D());
	//	NewTransform = AdjustTransform(NewTransform);
	//	NewTransform = ClampTransform(NewTransform);
	//	return NewTransform;
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
	//virtual FTransform AdjustTransform(const FTransform& Transform) const override
	//{
	//	return Transform;
	//}



private:
	FKey Key;
	float SphereRadius;
	FVector FirstClosestPoint;
	FTransform OriginalRelativeTransform;
};
