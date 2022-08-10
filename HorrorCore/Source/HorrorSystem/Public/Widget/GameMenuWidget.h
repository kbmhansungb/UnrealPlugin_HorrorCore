// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuWidget.generated.h"

class UOptionWidget;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativePreConstruct() override
	//{
	//	Super::NativePreConstruct();
	//}

	UFUNCTION(BlueprintCallable)
	void QuitGame()
	{
	}

	UFUNCTION(BlueprintCallable)
	void OpenOption()
	{
	}

protected:
	UPROPERTY(Meta = (BindWidget))
	UOptionWidget* OptionWidget;
};
