// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorInventoryComponent.h"
#include "HorrorCore.h"
#include <Kismet/GameplayStatics.h>

UHorrorInventoryComponent::UHorrorInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Space = EWidgetSpace::World;
}

void UHorrorInventoryComponent::SetWidget(UUserWidget* NewWidget)
{
	Super::SetWidget(NewWidget);
	InternalInitWidget();
}

void UHorrorInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHorrorInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHorrorInventoryComponent::InitWidget()
{
	UWidgetComponent::InitWidget();
	InternalInitWidget();
}

bool UHorrorInventoryComponent::IsStorable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const
{
	return Inventory.IsStorable(Iteminterface, Index);
}

bool UHorrorInventoryComponent::StoreItem_Implementation(const TScriptInterface<IHorrorItemActorInterface>& ItemActor, FIntPoint Index)
{
	if (!ItemActor.GetObject())
	{
		return false;
	}

	bool Result = Inventory.TryStoreItemActor(ItemActor, Index);
	
	if (Result)
	{
		InventoryChangedDelegate.Broadcast();
	}

	return Result;
}

bool UHorrorInventoryComponent::IsTakable_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	return Inventory.IsTakable(Index, Iteminterface);;
}

bool UHorrorInventoryComponent::TakeItem_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemActorInterface>& ItemActor)
{
	bool Result = Inventory.TryTakeItemActor(this, this->GetComponentTransform(), Index, ItemActor);

	if (Result)
	{
		InventoryChangedDelegate.Broadcast();
	}

	return Result;
}

void UHorrorInventoryComponent::GetInventorySize_Implementation(FIntSize2D& InventorySize) const
{
	InventorySize = Inventory.InventorySize;
}

void UHorrorInventoryComponent::CopyItemBundleArray_Implementation(TArray<FHorrorItem2DInventoryData>& InventoryDataArray) const
{
	InventoryDataArray = TArray<FHorrorItem2DInventoryData>(Inventory.Items);
}

void UHorrorInventoryComponent::InternalInitWidget()
{
	UInventoryWidget* InventoryWidget = Cast<UInventoryWidget>(GetWidget());
	if (InventoryWidget)
	{
		InventoryWidget->Inventory = this;
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(HorrorEventLog, Error, TEXT("Cannot cast to UInventoryWidget."));
	}
#endif
}
