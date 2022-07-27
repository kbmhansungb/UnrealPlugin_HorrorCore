// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorSphereMoveableComponent.h"
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
	//ApplyAxisMoveable(Ray.Origin, Ray.Direction);

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

	//PreAxisMoveable(Hit);
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

void UHorrorAxisRotationComponent::PreMoveable() 
{
}

void UHorrorAxisRotationComponent::PostMoveable() 
{
}

FVector UHorrorAxisRotationComponent::GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const
{
	FVector Result;
	FMath::SphereDistToLine(GetComponentLocation(), SphereRadius, Origin, Direction, Result);

	return Result;
}

void UHorrorAxisRotationComponent::SetFirstIntersectionPoint(const FHitResult& HitLocation)
{
	SphereRadius = (HitLocation.Location - GetComponentLocation()).Size();
}

