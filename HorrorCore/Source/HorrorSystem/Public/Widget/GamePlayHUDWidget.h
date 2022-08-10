// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UGamePlayHUDWidget : public UUserWidget
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
