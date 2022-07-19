// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorAxisRotationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Engine.h"

#include "DrawDebugHelpers.h"

UHorrorAxisRotationComponent::UHorrorAxisRotationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHorrorAxisRotationComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		if (UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Child))
		{
			FScriptDelegate ClickedMouse;
			ClickedMouse.BindUFunction(this, FName("ClickedMouse"));
			Primitive->OnClicked.Add(ClickedMouse);

			FScriptDelegate ReleaseMouse;
			ReleaseMouse.BindUFunction(this, FName("ReleasedMouse"));
			Primitive->OnReleased.Add(ReleaseMouse);
		}
	}

	SetComponentTickEnabled(false);
}

void UHorrorAxisRotationComponent::SetComponentTickEnabled(bool bEnabled)
{
	Super::SetComponentTickEnabled(bEnabled);

	if (!bEnabled)
	{
		Key = FKey();
	}
}

void UHorrorAxisRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	FRay Ray = GetNowMouseRay(PC);
	ApplyAxisMoveable(Ray.Origin, Ray.Direction);

	if ( Key.IsValid() && !(PC->GetInputAnalogKeyState(Key) > 0.f))
	{
		SetComponentTickEnabled(false);
	}
}

void UHorrorAxisRotationComponent::ClickedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetComponentTickEnabled(true);
	Key = ButtonPressed;

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	FRay Ray = GetNowMouseRay(PC);
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(PC->GetPawn());
	GetWorld()->LineTraceSingleByChannel(Hit, Ray.Origin, Ray.Origin + Ray.Direction * 1000.f, ECollisionChannel::ECC_Camera, Params);

	PreAxisMoveable(Hit);
}

void UHorrorAxisRotationComponent::ReleasedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetComponentTickEnabled(false);
}

FRay UHorrorAxisRotationComponent::GetNowMouseRay(APlayerController* PC)
{
	FRay Ray;
	FVector2D MousePosition;

	PC->GetMousePosition(MousePosition.X, MousePosition.Y);
	UGameplayStatics::DeprojectScreenToWorld(PC, MousePosition, Ray.Origin, Ray.Direction);

	return Ray;
}

void UHorrorAxisRotationComponent::PreAxisMoveable(const FHitResult& HitResult)
{
	SphereRadius = (HitResult.Location - GetComponentLocation()).Size();
	FirstClosestPoint = GetIntersectionPoint(HitResult.TraceStart, (HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal());
	OriginalRelativeTransform = GetRelativeTransform();
}

void UHorrorAxisRotationComponent::ApplyAxisMoveable(const FVector& Origin, const FVector& Direction)
{
	const FVector& OutClosestPoint = GetIntersectionPoint(Origin, Direction);
	SetRelativeTransform(GetNewReleativeTransform(OutClosestPoint));
}

FVector UHorrorAxisRotationComponent::GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const
{
	FVector OutClosestPoint;

	FMath::SphereDistToLine(GetComponentLocation(), SphereRadius, Origin, Direction, OutClosestPoint);
	DrawDebugSphere(GetWorld(), FirstClosestPoint, 5.0f, 16, FColor::Blue);
	DrawDebugSphere(GetWorld(), OutClosestPoint, 5.0f, 16, FColor::Green);

	return OutClosestPoint;
}

FTransform UHorrorAxisRotationComponent::GetNewReleativeTransform(const FVector& OutClosestPoint) const
{
	const FVector& VO = FirstClosestPoint.GetSafeNormal();
	const FVector& V1 = (OutClosestPoint - GetComponentLocation()).GetSafeNormal();

	// 개선할 수 있음.
	const FVector& Axis = (VO ^ V1).GetSafeNormal();
	const float& Rad = FMath::Acos(V1 | VO);
	const FQuat& Quat = FQuat(Axis, Rad);
	
	FTransform NewTransform = FTransform(Quat * OriginalRelativeTransform.GetRotation(), OriginalRelativeTransform.GetLocation(), OriginalRelativeTransform.GetScale3D());
	NewTransform = AdjustTransform(NewTransform);
	NewTransform = ClampTransform(NewTransform);
	return NewTransform;
}

FTransform UHorrorAxisRotationComponent::ClampTransform(const FTransform& Transform) const
{
	if (!GetAttachParent())
	{
		return Transform;
	}
	const FVector& Axis = GetAttachParent()->GetUpVector();
	
	FQuat Swing, Twist;
	Transform.GetRotation().ToSwingTwist(Axis, Swing, Twist);

	float TwistAngle = FMath::RadiansToDegrees((Twist.Z > 0.f) ? Twist.GetAngle() : -Twist.GetAngle());
	TwistAngle = FMath::Clamp(TwistAngle, TwistLimit.X, TwistLimit.Y);

	const FQuat& LimitedTwist = FQuat(Axis, FMath::DegreesToRadians(TwistAngle));

	DrawDebugLine(GetWorld(), GetComponentLocation(), GetComponentLocation() + Axis * (SphereRadius + 10.0f), FColor::Blue);
	UE_LOG(LogTemp, Display, TEXT("Twist : %s, Angle : %f, Limited Twist : %s"), *Twist.ToString(), TwistAngle , *LimitedTwist.ToString());

	
	return FTransform(LimitedTwist * Swing, Transform.GetLocation(), Transform.GetScale3D());

	//return Transform;
}

FTransform UHorrorAxisRotationComponent::AdjustTransform(const FTransform& Transform) const
{
	return Transform;
}
