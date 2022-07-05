// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_UsingItem.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_UsingItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativePreConstruct() override
	//{
	//	Super::NativePreConstruct();
	//}

	void UsingItem()
	{

	}

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
