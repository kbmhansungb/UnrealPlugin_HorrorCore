// 2022 06    Bum moo, Kim    Free copyright

#include "HorrorHandComponent.h"
#include "HorrorItemActorInterface.h"
#include <GameFramework/Actor.h>
#include <Kismet/KismetMathLibrary.h>

UHorrorHandComponent::UHorrorHandComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHorrorHandComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UHorrorHandComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Lerp(DeltaTime);
}

bool UHorrorHandComponent::IsHoldable(const EHandType Type, AActor* Actor)
{
	if (
		(GetHoldStruct(Type)->HoldItem == nullptr) && 
		(Actor->GetClass()->ImplementsInterface(UHorrorItemActorInterface::StaticClass()))
		)
	{
		return IHorrorItemActorInterface::Execute_IsHoldable(Actor, this);
	}
	return false;
}

void UHorrorHandComponent::Hold(const EHandType Type, AActor* Actor)
{
	FHoldStruct* HandStruct = GetHoldStruct(Type);
	HandStruct->HoldItem = Actor;
	SetStart(Type, Actor);
}

void UHorrorHandComponent::Swap()
{
	auto Temp = RightHand.HoldItem;
	RightHand.HoldItem = LeftHand.HoldItem;
	LeftHand.HoldItem = Temp;

	if (RightHand.HoldItem)
	{
		SetStart(EHandType::RIGHT, RightHand.HoldItem);
	}

	if (LeftHand.HoldItem)
	{
		SetStart(EHandType::LEFT, LeftHand.HoldItem);
	}
}

void UHorrorHandComponent::Put(const EHandType Type)
{
	FHoldStruct* HandStruct = GetHoldStruct(Type);
	HandStruct->HoldItem = nullptr;
}

void UHorrorHandComponent::Lerp(float Deleta)
{
	if (RightHand.HoldItem)
	{
		RightHand.HoldItem->SetActorTransform(UKismetMathLibrary::TInterpTo(RightHand.HoldItem->GetActorTransform(), FTransform(RightHand.RelativePosition) * GetComponentTransform(), Deleta, LerpSpeed));
	}

	if (LeftHand.HoldItem)
	{
		LeftHand.HoldItem->SetActorTransform(UKismetMathLibrary::TInterpTo(LeftHand.HoldItem->GetActorTransform(), FTransform(LeftHand.RelativePosition) * GetComponentTransform(), Deleta, LerpSpeed));
	}
}

void UHorrorHandComponent::SetStart(const EHandType Type, AActor* Actor)
{
	FTransform Transform = GetComponentTransform();

	switch (Type)
	{
	case EHandType::LEFT:
		Transform = FTransform(LeftHand.RelativePosition + StartOffset) * Transform;
		break;
	case EHandType::RIGHT:
		Transform = FTransform(RightHand.RelativePosition + StartOffset) * Transform;
		break;
	default:
		check(false && "Need add case");
		return;
	}

	Actor->SetActorTransform(Transform);
}

