// 2022 06    Bum moo, Kim    Free copyright


#include "Widget_Inventory.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Widget_ItemList.h"

void UWidget_Inventory::NativePreConstruct()
{
	Super::NativePreConstruct();

	CreateItemList();
}

void UWidget_Inventory::CreateItemList()
{
	if (ItemListClass.Get() == nullptr)
	{
		return;
	}

	ItemList = WidgetTree->ConstructWidget<UWidget_ItemList>(ItemListClass.Get());
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(MainCanvas->AddChild(ItemList));
	CanvasSlot->SetSize(ItemList->GetSlotSize());
}

void UWidget_Inventory::ReceiveInventoryChange()
{

}

void UWidget_Inventory::ReceiveItemChange()
{
}
