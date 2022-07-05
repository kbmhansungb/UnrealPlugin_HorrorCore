// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_GamePlayHUD.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_GamePlayHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativePreConstruct() override
	//{
	//	Super::NativePreConstruct();
	//}

	UFUNCTION(BlueprintCallable)
	void ReceiveLookAtChange()
	{
	}

	UFUNCTION(BlueprintCallable)
	void ReceiveHPChange()
	{
	}

	UFUNCTION(BlueprintCallable)
	void ReceiveNotice()
	{
	}

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveGamePlayHUD;
};
