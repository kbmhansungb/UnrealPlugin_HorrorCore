// 2022 06    Bum moo, Kim    Free copyright

#include "HorrorHandComponent.h"
#include "HorrorHoldableInterface.h"
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

bool UHorrorHandComponent::IsDominanceHand_Implementation() const
{
	return true;
}

TScriptInterface<IHorrorHoldableInterface> UHorrorHandComponent::GetHoldable_Implementation() const
{
	return GetHoldStruct(HandDominance)->HoldItem;
}

bool UHorrorHandComponent::IsEmptyHand(const EHandType Type)
{
	return GetHoldStruct(Type)->HoldItem.GetObject() == nullptr;
}

void UHorrorHandComponent::Hold(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable)
{
	GetHoldStruct(Type)->HoldItem = Holdable;

	SetStart(Type, Holdable);
}

void UHorrorHandComponent::Swap()
{
	auto Temp = RightHand.HoldItem;
	RightHand.HoldItem = LeftHand.HoldItem;
	LeftHand.HoldItem = Temp;

	if (RightHand.HoldItem.GetObject())
	{
		SetStart(EHandType::RIGHT, RightHand.HoldItem);
	}

	if (LeftHand.HoldItem.GetObject())
	{
		SetStart(EHandType::LEFT, LeftHand.HoldItem);
	}
}

void UHorrorHandComponent::Release(const EHandType Type)
{
	FHoldStruct* HandStruct = GetHoldStruct(Type);
	HandStruct->HoldItem = nullptr;
}

void UHorrorHandComponent::Lerp(float Deleta)
{
	if (RightHand.HoldItem.GetObject())
	{
		IHorrorHoldableInterface::Execute_LerpHoldableTransform(RightHand.HoldItem.GetObject(), FTransform(RightHand.RelativePosition) * GetComponentTransform());
	}

	if (LeftHand.HoldItem.GetObject())
	{
		IHorrorHoldableInterface::Execute_LerpHoldableTransform(LeftHand.HoldItem.GetObject(), FTransform(LeftHand.RelativePosition) * GetComponentTransform());
	}
}

void UHorrorHandComponent::SetStart(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable)
{
	FTransform Transform = GetComponentTransform();
	Transform = FTransform(GetHoldStruct(Type)->RelativePosition + StartOffset) * Transform;

	IHorrorHoldableInterface::Execute_SetHoldableTransform(Holdable.GetObject(), Transform);
}

const FHoldStruct* UHorrorHandComponent::GetHoldStruct(const EHandType Type) const
{
	switch (Type)
	{
	case EHandType::LEFT:
		return &LeftHand;
		break;
	case EHandType::RIGHT:
		return &RightHand;
		break;
	default:
		check(false && "Need add case");
		return nullptr;
	}
}

FHoldStruct* UHorrorHandComponent::GetHoldStruct(const EHandType Type)
{
	switch (Type)
	{
	case EHandType::LEFT:
		return &LeftHand;
		break;
	case EHandType::RIGHT:
		return &RightHand;
		break;
	default:
		check(false && "Need add case");
		return nullptr;
	}
}

const FHoldStruct& UHorrorHandComponent::GetRightStruct() const
{
	return RightHand;
}

const FHoldStruct& UHorrorHandComponent::GetLeftStruct() const
{
	return LeftHand;
}
