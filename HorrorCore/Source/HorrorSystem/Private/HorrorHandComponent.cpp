// 2022 06    Bum moo, Kim    Free copyright

#include "HorrorHandComponent.h"
#include "HorrorHoldableInterface.h"
#include <GameFramework/Actor.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

void FHoldStruct::ReleaseHoldItem(const TScriptInterface<IHorrorHandInterface>& HandInterface)
{
	if (!HoldItem.GetObject())
	{
		return;
	}

	if (HoldItem.GetObject()->GetClass()->ImplementsInterface(UHorrorHoldableInterface::StaticClass()))
	{
		IHorrorHoldableInterface::Execute_ResponseReleaseHoldable(HoldItem.GetObject(), HandInterface);
	}

	HoldItem = nullptr;
}

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

void UHorrorHandComponent::GetHoldItem_Implementation(bool& IsHold, TScriptInterface<IHorrorHoldableInterface>& HoldableItem) const
{
	// 없는 손으로는 잡을 수 없으므로
	IsHold = true;
	HoldableItem = TScriptInterface<IHorrorHoldableInterface>();

	const FHoldStruct* HoldStruct = GetHoldStruct(HandDominance);

	if (HoldStruct)
	{
		IsHold = HoldStruct->HoldItem.GetObject() != nullptr;
		HoldableItem = HoldStruct->HoldItem.GetObject();
	}
}

TScriptInterface<IHorrorHoldableInterface> UHorrorHandComponent::GetHoldable_Implementation() const
{
	return GetHoldStruct(HandDominance)->HoldItem;
}

void UHorrorHandComponent::GetHoldablePutLocation_Implementation(FHitResult& HitResult) const
{
	HitResult = FHitResult();

	const FVector& Position = UGameplayStatics::GetPlayerController(this, 0)->PlayerCameraManager->GetCameraLocation();
	const FVector& Forward = UGameplayStatics::GetPlayerController(this, 0)->PlayerCameraManager->GetActorForwardVector();

	if (UKismetSystemLibrary::LineTraceSingle(this, Position, Position + Forward * HandLength, TracePutLocationQueryType, true, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true) &&
		CheckPutable(HitResult))
	{
		return;
	}

	if (UKismetSystemLibrary::LineTraceSingle(this, Position, Position + -GetOwner()->GetActorUpVector() * HandLength, TracePutLocationQueryType, true, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true) &&
		CheckPutable(HitResult))
	{
		return;
	}

	HitResult.Location = GetOwner()->GetActorTransform().GetTranslation();
	HitResult.Normal = FVector::UpVector;
}

bool UHorrorHandComponent::IsEmptyHand(const EHandType Type)
{
	return GetHoldStruct(Type)->HoldItem.GetObject() == nullptr;
}

bool UHorrorHandComponent::Hold(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable)
{
	if (GetHoldStruct(Type)->HoldItem == nullptr)
	{
		GetHoldStruct(Type)->HoldItem = Holdable;
		SetStart(Type, Holdable);

		return true;
	}

	return false;
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
	if (HandStruct)
	{
		HandStruct->ReleaseHoldItem(this);
	}
}

void UHorrorHandComponent::Lerp_Implementation(float Deleta)
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

bool UHorrorHandComponent::CheckPutable(const FHitResult& HitResult) const
{
	static constexpr float RadFrom30Degree = 0.86602540378f;
	check(HitResult.bBlockingHit);

	return FVector::DotProduct(HitResult.Normal, FVector::UpVector) > RadFrom30Degree;
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
		return &GetLeftStruct();
		break;
	case EHandType::RIGHT:
		return &GetRightStruct();
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
		return &GetLeftStruct();
		break;
	case EHandType::RIGHT:
		return &GetRightStruct();
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

FHoldStruct& UHorrorHandComponent::GetRightStruct()
{
	return RightHand;
}

FHoldStruct& UHorrorHandComponent::GetLeftStruct()
{
	return LeftHand;
}

bool UHorrorHandComponent::CompareHoldedObject(IHorrorHoldableInterface* LeftObject, IHorrorHoldableInterface* RightObject) const
{
	return LeftHand.HoldItem == LeftObject && RightHand.HoldItem == RightObject;
}