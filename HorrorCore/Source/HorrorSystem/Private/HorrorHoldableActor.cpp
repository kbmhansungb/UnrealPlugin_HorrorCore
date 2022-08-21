// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorHoldableActor.h"
#include <Components/StaticMeshComponent.h>
#include <ActorSequence/Public/ActorSequenceComponent.h>
#include <ActorSequence/Public/ActorSequencePlayer.h>
#include <Kismet/KismetMathLibrary.h>
#include <HorrorSystem/Public/HorrorHandInterface.h>

AHorrorHoldableActor::AHorrorHoldableActor()
{
	//PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	ItemMeshComponent->SetupAttachment(RootComponent);

	PutSequence = CreateDefaultSubobject<UActorSequenceComponent>(FName("PutSequence"));
}

void AHorrorHoldableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHorrorHoldableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* AHorrorHoldableActor::GetHoldableActor_Implementation() const
{
	const AActor* Ptr = this;
	return const_cast<AActor*>(Ptr);
}

bool AHorrorHoldableActor::IsHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) const
{
	return true;
}

void AHorrorHoldableActor::ResponseHoldHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface)
{
	SetSequence(false);
}

void AHorrorHoldableActor::SetHoldableTransform_Implementation(const FTransform& DesireTransform)
{
	this->SetActorTransform(DesireTransform);
}

void AHorrorHoldableActor::LerpHoldableTransform_Implementation(const FTransform& DesireTransform)
{
	const FTransform& NewTransform = UKismetMathLibrary::TLerp(GetActorTransform(), DesireTransform, 0.2f);

	this->SetActorTransform(NewTransform);
}

void AHorrorHoldableActor::ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface)
{
	FHitResult HitResult;
	IHorrorHandInterface::Execute_GetHoldablePutLocation(HandInterface.GetObject(), HitResult);
	
	FVector Normal = HitResult.Normal;
	FVector WorldLocation = HitResult.Location;

	AddActorWorldTransform(
		FTransform(
			GetTransformQuat(Normal),
			WorldLocation - GetActorLocation() + FVector(0.f, 0.f, 20.f)
		),
		false, nullptr, ETeleportType::None
	);
	AddActorWorldRotation(GetTransformQuat(Normal), false, nullptr, ETeleportType::None);
	SetSequence(true);
}

void AHorrorHoldableActor::SetSequence(bool PlayAnim)
{
	if (!PutSequence) return;
	if (!PutSequence->GetSequencePlayer()) return;

	if (PlayAnim)
	{
		PutSequence->GetSequencePlayer()->Play();
	}
	else
	{
		PutSequence->GetSequencePlayer()->GoToEndAndStop();
	}
}

FQuat AHorrorHoldableActor::GetTransformQuat(const FVector& DesireNormal)
{
	check(DesireNormal.IsNormalized());

	const FVector& Axis = FVector::CrossProduct(GetActorUpVector(), DesireNormal).GetSafeNormal();
	const float& Rad = FMath::Acos(FVector::DotProduct(GetActorUpVector(), DesireNormal));

	return FQuat(Axis, Rad);
}
