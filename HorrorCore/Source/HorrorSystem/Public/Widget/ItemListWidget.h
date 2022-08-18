// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "HorrorItemInterface.h"
#include "ItemListWidget.generated.h"

class IHorrorInventoryInterface;
class UImage;
class UItemSlotWidget;
class UCanvasPanel;
class UTextureRenderTarget2D;
class UInventoryWidget;

USTRUCT(BlueprintType)
struct FItemSlotForm
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemSlotWidget> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SquareSize = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Padding;
};

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UItemListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	UInventoryWidget* Inventory;

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
	TArray<UItemSlotWidget*> ItemSlots;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetSlotOffset(const int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetSlotOffset2D(const int32 X, const int32 Y) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetCanvasSize(const int32 X, const int32 Y) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetCanvasSize2D() const;
};

