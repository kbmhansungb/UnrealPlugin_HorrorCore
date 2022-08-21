// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorHoldableActor.h"
#include <Components/StaticMeshComponent.h>
#include <ActorSequence/Public/ActorSequenceComponent.h>

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
	return nullptr;
}

bool AHorrorHoldableActor::IsHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) const
{
	return false;
}

void AHorrorHoldableActor::ResponseHoldHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface)
{
}

void AHorrorHoldableActor::SetHoldableTransform_Implementation(const FTransform& DesireTransform)
{
}

void AHorrorHoldableActor::LerpHoldableTransform_Implementation(const FTransform& DesireTransform)
{
}

void AHorrorHoldableActor::ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface)
{
}
