// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MainMenu.generated.h"

class UButton;
class UWidget_Option;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	void ContinueGame();

	UFUNCTION(BlueprintCallable)
	void NewStartGame();

	UFUNCTION(BlueprintCallable)
	void OpenOption();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

protected:
	UPROPERTY(Meta = (BindWidget))
	UButton* ContinueButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* NewStartButton;
	
	UPROPERTY(Meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(Meta = (BindWidget))
	UWidget_Option* OptionWidget;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
