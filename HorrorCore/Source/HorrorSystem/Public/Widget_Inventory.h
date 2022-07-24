// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Inventory.generated.h"

class UCanvasPanel;
class UWidget_ItemList;
class IHorrorInventoryInterface;

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TScriptInterface<IHorrorInventoryInterface> Inventory;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidget_ItemList* ItemList;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* MainCanvas;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
