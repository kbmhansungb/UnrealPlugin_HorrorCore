// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UOptionWidget;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UMainMenuWidget : public UUserWidget
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
	UOptionWidget* OptionWidget;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ActiveAnimation;
};
