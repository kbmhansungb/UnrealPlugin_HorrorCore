// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_Inventory : public UUserWidget
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

	void ChangeKey()
	{

	}

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
