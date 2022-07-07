// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Inventory.generated.h"

class UCanvasPanel;
class UWidget_ItemList;

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UWidget_ItemList> ItemListClass;

	UPROPERTY(BlueprintReadOnly)
	UWidget_ItemList* ItemList;

protected:
	void CreateItemList();

protected:
	UFUNCTION(BlueprintCallable)
	void ReceiveInventoryChange();

	UFUNCTION(BlueprintCallable)
	void ReceiveItemChange();

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
