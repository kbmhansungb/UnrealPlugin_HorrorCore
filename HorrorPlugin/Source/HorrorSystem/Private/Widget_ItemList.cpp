// 2022 06    Bum moo, Kim    Free copyright


#include "Widget_ItemList.h"
#include "HorrorInventoryComponent.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Widget_ItemSlot.h"

void UWidget_ItemList::NativePreConstruct()
{
	Super::NativePreConstruct();

	CreateItemList();
}

void UWidget_ItemList::CreateItemList()
{
	if (ItemSlotForm.Class.Get() == nullptr)
	{
		return;
	}

	for (int X = 0; X < ItemListSize.X; ++X)
		for (int Y = 0; Y < ItemListSize.Y; ++Y)
		{
			UWidget_ItemSlot* ItemSlot = WidgetTree->ConstructWidget<UWidget_ItemSlot>(ItemSlotForm.Class.Get());
			ItemSlot->Index = FIntPoint(X, Y);

			UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(MainCanvas->AddChild(ItemSlot));
			CanvasSlot->SetPosition(GetSlotOffset(X, Y));
			CanvasSlot->SetSize(FVector2D(ItemSlotForm.LengthOfSide));
		}

	FVector2D SlotSize = GetSlotSize(ItemListSize.X, ItemListSize.Y);
	{
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Background->Slot);
		CanvasSlot->SetSize(SlotSize);
	}

	this->SetDesiredSizeInViewport(SlotSize);
}

void UWidget_ItemList::ReceiveInventoryChange()
{

}

void UWidget_ItemList::ReceiveItemChange()
{
}
