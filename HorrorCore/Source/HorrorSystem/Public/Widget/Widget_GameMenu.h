// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_GameMenu.generated.h"

class UWidget_Option;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_GameMenu : public UUserWidget
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
	UWidget_Option* Option;
};
