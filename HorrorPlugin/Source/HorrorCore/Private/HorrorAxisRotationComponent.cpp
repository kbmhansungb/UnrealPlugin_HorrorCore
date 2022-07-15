// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorAxisRotationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/PrimitiveComponent.h"

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

void UHorrorAxisRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	FRay Ray;
	FVector2D MousePosition;
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->GetMousePosition(MousePosition.X, MousePosition.Y);
	UGameplayStatics::DeprojectScreenToWorld(PC, MousePosition, Ray.Origin, Ray.Direction);

	FSphere Sphere;
	Sphere.Center = GetComponentLocation();
	Sphere.W = SphereRadius;

	FVector OutClosedPoint;
	FMath::SphereDistToLine(Sphere.Center, Sphere.W, Ray.Origin, Ray.Direction, OutClosedPoint);
	DrawDebugSphere(GetWorld(), OutClosedPoint, 5.0f, 16, FColor::Green);

	FTransform NewVirtualTransform = FTransform(UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), OutClosedPoint), OutClosedPoint).GetRelativeTransform(GetComponentTransform());
	ActiveComponent->SetRelativeTransform(RelativeTransform * NewVirtualTransform);

	if ( !(PC->GetInputAnalogKeyState(Key) > 0.f) )
	{
		SetComponentTickEnabled(false);
	}
}

void UHorrorAxisRotationComponent::ClickedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetComponentTickEnabled(true);

	FRay Ray;
	FVector2D MousePosition;
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->GetMousePosition(MousePosition.X, MousePosition.Y);
	UGameplayStatics::DeprojectScreenToWorld(PC, MousePosition, Ray.Origin, Ray.Direction);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(PC->GetPawn());
	GetWorld()->LineTraceSingleByChannel(Hit, Ray.Origin, Ray.Origin + Ray.Direction * 1000.f, ECollisionChannel::ECC_Camera, Params);
	DrawDebugSphere(GetWorld(), Hit.Location, 5.0f, 16, FColor::Blue, false, 5.0f);

	ActiveComponent = Hit.Component.Get();
	Key = ButtonPressed;
	SphereRadius = (Hit.Location - GetComponentLocation()).Size();

	FSphere Sphere;
	Sphere.Center = GetComponentLocation();
	Sphere.W = SphereRadius;

	FVector OutClosedPoint;
	FMath::SphereDistToLine(Sphere.Center, Sphere.W, Ray.Origin, Ray.Direction, OutClosedPoint);
	DrawDebugSphere(GetWorld(), OutClosedPoint, 5.0f, 16, FColor::Green);

	VirtualTransform = FTransform(UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), OutClosedPoint), OutClosedPoint).GetRelativeTransform(GetComponentTransform());
	RelativeTransform = FTransform(ActiveComponent->GetRelativeTransform().GetRelativeTransform(VirtualTransform));
}

void UHorrorAxisRotationComponent::ReleasedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetComponentTickEnabled(false);
}

void UHorrorAxisRotationComponent::ApplyAxisMovealbe_Implementation(USceneComponent* Target, const FVector2D&)
{
}

