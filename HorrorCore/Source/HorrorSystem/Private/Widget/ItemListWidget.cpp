// 2022 06    Bum moo, Kim    Free copyright


#include "Widget/ItemListWidget.h"
#include "HorrorInventoryComponent.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Widget/ItemSlotWidget.h"

int32 UItemListWidget::GetSlotOffset(const int32 SlotIndex) const
{
	return SlotIndex * ItemSlotForm.SquareSize + (SlotIndex + 1) * ItemSlotForm.Padding;
}

FVector2D UItemListWidget::GetSlotOffset2D(const int32 X, const int32 Y) const
{
	return FVector2D(GetSlotOffset(X), GetSlotOffset(Y));
}

FVector2D UItemListWidget::GetCanvasSize(const int32 X, const int32 Y) const
{
	return FVector2D(
		X * ItemSlotForm.SquareSize + (X + 1) * ItemSlotForm.Padding,
		Y * ItemSlotForm.SquareSize + (Y + 1) * ItemSlotForm.Padding
	);
}

FVector2D UItemListWidget::GetCanvasSize2D() const
{
	return GetCanvasSize(ItemListSize.X, ItemListSize.Y);
}

