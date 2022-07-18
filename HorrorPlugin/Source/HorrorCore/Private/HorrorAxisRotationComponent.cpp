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
	FVector OutClosestPoint = GetIntersectionPoint(Ray.Origin, Ray.Direction);

	FTransform NewVirtualTransform = GetVirtualTransform(OutClosestPoint);
	ActiveComponent->SetRelativeTransform(RelativeTransform * NewVirtualTransform);

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

	ActiveComponent = Hit.Component.Get();
	SphereRadius = (Hit.Location - GetComponentLocation()).Size();
	FirstClosestPoint = GetIntersectionPoint(Ray.Origin, Ray.Direction);

	VirtualTransform = GetVirtualTransform(FirstClosestPoint);
	RelativeTransform = FTransform(ActiveComponent->GetRelativeTransform().GetRelativeTransform(VirtualTransform));
}

void UHorrorAxisRotationComponent::ReleasedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetComponentTickEnabled(false);
}

FVector UHorrorAxisRotationComponent::GetIntersectionPoint(const FVector& Origin, const FVector& Direction)
{
	FVector OutClosestPoint;

	FMath::SphereDistToLine(GetComponentLocation(), SphereRadius, Origin, Direction, OutClosestPoint);
	DrawDebugSphere(GetWorld(), FirstClosestPoint, 5.0f, 16, FColor::Blue);
	DrawDebugSphere(GetWorld(), OutClosestPoint, 5.0f, 16, FColor::Green);

	return OutClosestPoint;
}

FRay UHorrorAxisRotationComponent::GetNowMouseRay(APlayerController* PC)
{
	FRay Ray;
	FVector2D MousePosition;

	PC->GetMousePosition(MousePosition.X, MousePosition.Y);
	UGameplayStatics::DeprojectScreenToWorld(PC, MousePosition, Ray.Origin, Ray.Direction);

	return Ray;
}

FTransform UHorrorAxisRotationComponent::GetVirtualTransform(const FVector& OutClosestPoint)
{
	FVector V = (OutClosestPoint - GetComponentLocation()).GetSafeNormal();
	V = GetComponentRotation().UnrotateVector(V);

	const FVector& Axis = (V ^ FVector::UpVector).GetSafeNormal();
	const float& Rad = -FMath::Acos(V | FVector::UpVector);
	FQuat Quat = FQuat(Axis, Rad);

	return FTransform(Quat);
}
