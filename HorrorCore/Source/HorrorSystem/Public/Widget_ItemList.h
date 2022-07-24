// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "HorrorItemInterface.h"
#include "Widget_ItemList.generated.h"

class IHorrorInventoryInterface;
class UImage;
class UWidget_ItemSlot;
class UCanvasPanel;
class UTextureRenderTarget2D;
class UWidget_Inventory;

USTRUCT(BlueprintType)
struct FItemSlotForm
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_ItemSlot> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SquareSize = 90;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	UWidget_Inventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntSize2D ItemListSize{1, 1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemSlotForm ItemSlotForm;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UCanvasPanel* MainCanvas;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UImage* Background;
	
    UPROPERTY(BlueprintReadWrite, Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWidget_ItemSlot*> ItemSlots;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetSlotOffset(const int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetSlotOffset2D(const int32 X, const int32 Y) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetCanvasSize(const int32 X, const int32 Y) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetCanvasSize() const;
};

