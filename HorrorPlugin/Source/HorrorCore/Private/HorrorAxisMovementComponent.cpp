// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorAxisMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"

// IHorrorAxisMoveableInterface에서 상속됨

UHorrorAxisMovementComponent::UHorrorAxisMovementComponent()
{
}

void UHorrorAxisMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHorrorAxisMovementComponent::ApplyAxisMovealbe_Implementation(USceneComponent* Target, const FVector2D&)
{
	FVector2D MousePosition;
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->GetMousePosition(MousePosition.X, MousePosition.Y);

	FVector WorldPosition, WorldDirection;
	
	UGameplayStatics::DeprojectScreenToWorld(PC, MousePosition, WorldPosition, WorldDirection);
	FVector HitPos = FMath::RayPlaneIntersection(WorldPosition, WorldDirection, FPlane(GetComponentLocation(), GetUpVector()));

	DrawDebugSphere(GetWorld(), HitPos, 5.0f, 8, FColor::Green);

	ApplyAxisMoveableToChild(Target, FVector2D(GetComponentTransform().InverseTransformPosition(HitPos)));
}

void UHorrorAxisMovementComponent::ApplyAxisMoveableToChild(USceneComponent* Target, const FVector2D& RelativePos)
{
	FHitResult HitResult;

	const FVector& Location = Target->GetRelativeLocation();
	FVector2D Vector = RelativePos - FVector2D(Location);
	float Size = Vector.Size();
	
	float Multifly = FMath::Min(Size, MaxStepSize) / Size;
	const FVector2D& Step = (Size > FLT_EPSILON) ? FVector2D(Location) + (Vector * Multifly) : RelativePos;

	Target->SetRelativeLocation(FVector(
		FMath::Clamp(Step.X, XRange.X, XRange.Y),
		FMath::Clamp(Step.Y, YRange.X, YRange.Y),
		Location.Z
	), true, &HitResult);

	if (!HitResult.bBlockingHit)
	{
		return;
	}

	FVector2D Normal = FVector2D(GetComponentRotation().GetInverse().RotateVector(HitResult.Normal));
	Normal.Normalize();

	const FVector2D& Adjust = Normal * ((Vector | Normal) - FLT_EPSILON);
	Vector -= Adjust;

	const FVector2D& Step2 = FVector2D(Location) + Vector;

	Target->SetRelativeLocation(FVector(
		FMath::Clamp(Step2.X, XRange.X, XRange.Y),
		FMath::Clamp(Step2.Y, YRange.X, YRange.Y),
		Location.Z
	), true, &HitResult);

	if (!HitResult.bBlockingHit)
	{
		return;
	}

	Target->SetWorldLocation(HitResult.Location);
	//Target->SetRelativeLocation(Location);
}
