// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UOptionWidget : public UUserWidget
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
