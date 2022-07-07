// 2022 06    Bum moo, Kim    Free copyright

#include "HorrorHandComponent.h"
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

void UHorrorHandComponent::Hold(const EHandType Type, AActor* Actor)
{
	switch (Type)
	{
	case EHandType::LEFT:
		LeftHand.HoldItem = Actor;
		break;
	case EHandType::RIGHT:
		RightHand.HoldItem = Actor;
		break;
	default:
		check(false && "Need add case");
		return;
	}
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
	switch (Type)
	{
	case EHandType::LEFT:
		LeftHand.HoldItem = nullptr;
		break;
	case EHandType::RIGHT:
		RightHand.HoldItem = nullptr;
		break;
	default:
		check(false && "Need add case");
		return;
	}
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

