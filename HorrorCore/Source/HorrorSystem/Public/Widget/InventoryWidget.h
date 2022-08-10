// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UItemListWidget;
class IHorrorInventoryInterface;

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TScriptInterface<IHorrorInventoryInterface> Inventory;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UItemListWidget* ItemList;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* MainCanvas;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
