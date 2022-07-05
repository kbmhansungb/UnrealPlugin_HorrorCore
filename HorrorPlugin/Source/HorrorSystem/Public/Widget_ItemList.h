// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ItemList.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_ItemList : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativePreConstruct() override
	//{
	//	Super::NativePreConstruct();
	//}

	UFUNCTION(BlueprintCallable)
	void ReceiveInventoryChange()
	{
	}

	UFUNCTION(BlueprintCallable)
	void ReceiveItemChange()
	{
	}

	void QueryItemList()
	{

	}

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
