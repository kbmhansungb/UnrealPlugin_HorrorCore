// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "HorrorItemInterface.h"
#include "Widget_ItemList.generated.h"

class UWidget_Inventory;
class UImage;
class UWidget_ItemSlot;
class UCanvasPanel;
class UTextureRenderTarget2D;

USTRUCT(BlueprintType)
struct FItemSlotForm
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_ItemSlot> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LengthOfSide = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Padding;
};

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UWidget_ItemList : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* MainCanvas;

	UPROPERTY(Meta = (BindWidget))
	UImage* Background;
	
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;

protected:
	void CreateItemList();

protected:
	UWidget_Inventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntSize2D ItemListSize{1, 1};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemSlotForm ItemSlotForm;
	
public:

public:
	FORCEINLINE int32 GetSlotOffset(const int32 SlotIndex);
	FORCEINLINE FVector2D GetSlotOffset(const int32 X, const int32 Y);
	FORCEINLINE FVector2D GetSlotSize(const int32 X, const int32 Y);
	FORCEINLINE FVector2D GetSlotSize();;

protected:
	void ReceiveInventoryChange();
	void ReceiveItemChange();
};

int32 UWidget_ItemList::GetSlotOffset(const int32 SlotIndex)
{
	return SlotIndex * ItemSlotForm.LengthOfSide + (SlotIndex + 1) * ItemSlotForm.Padding;
}

FVector2D UWidget_ItemList::GetSlotOffset(const int32 X, const int32 Y)
{
	return FVector2D(GetSlotOffset(X), GetSlotOffset(Y));
}

FVector2D UWidget_ItemList::GetSlotSize(const int32 X, const int32 Y)
{
	return FVector2D(
		X * ItemSlotForm.LengthOfSide + (X + 1) * ItemSlotForm.Padding,
		Y * ItemSlotForm.LengthOfSide + (Y + 1) * ItemSlotForm.Padding
	);
}

FVector2D UWidget_ItemList::GetSlotSize()
{
	return GetSlotSize(ItemListSize.X, ItemListSize.Y);
}
