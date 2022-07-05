// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Option.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_Option : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativePreConstruct() override
	//{
	//	Super::NativePreConstruct();
	//}

	void ChangeLanguage()
	{

	}

	void ChangeBaseSound()
	{

	}

	void ChangeScreenBrightness()
	{
	
	}

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
