// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorInventoryComponent.h"
#include "HorrorCore.h"
#include <Kismet/GameplayStatics.h>

UHorrorInventoryComponent::UHorrorInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Space = EWidgetSpace::World;
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

	InventoryWidget = Cast<UInventoryWidget>(GetWidget());
	if (InventoryWidget)
	{
		InventoryWidget->Inventory = this;
	}
	else
	{
		UE_LOG(HorrorEventLog, Error, TEXT("Cannot cast to UInventoryWidget."));
	}
}

bool UHorrorInventoryComponent::IsStorable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const
{
	return Inventory.IsStorable(Iteminterface, Index);
}

bool UHorrorInventoryComponent::StoreItem_Implementation(const TScriptInterface<IHorrorItemActorInterface>& ItemActor, FIntPoint Index)
{
	return Inventory.TryStoreItemActor(ItemActor, Index);
}

bool UHorrorInventoryComponent::IsTakable_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	return Inventory.IsTakable(Index, Iteminterface);;
}

bool UHorrorInventoryComponent::TakeItem_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemActorInterface>& ItemActor)
{
	return Inventory.TryTakeItemActor(this, this->GetComponentTransform(), Index, ItemActor);
}

void UHorrorInventoryComponent::GetInventorySize_Implementation(FIntSize2D& InventorySize) const
{
	InventorySize = Inventory.InventorySize;
}
