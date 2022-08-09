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
	Super::InitWidget();

	InventoryWidget = Cast<UWidget_Inventory>(GetWidget());
	if (InventoryWidget)
	{
		InventoryWidget->Inventory = this;
	}
	else
	{
		UE_LOG(HorrorEventLog, Error, TEXT("Cannot cast to UWidget_Inventory."));
	}
}

bool UHorrorInventoryComponent::IsStorable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const
{
	return Inventory.IsStorable(Iteminterface, Index);
}

bool UHorrorInventoryComponent::StoreItem_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index)
{
	return Inventory.TryStoreItem(Iteminterface, Index);
}

bool UHorrorInventoryComponent::IsTakable_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	return Inventory.IsTakable(Index, Iteminterface);;
}

bool UHorrorInventoryComponent::TakeItem_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& Iteminterface)
{
	return Inventory.TryTakeItem(Index, Iteminterface);
}

void UHorrorInventoryComponent::GetInventorySize_Implementation(FIntSize2D& InventorySize) const
{
	InventorySize = Inventory.InventorySize;
}
