// 2022 06    Bum moo, Kim    Free copyright


#include "Widget/MainMenuWidget.h"
#include "Components/Button.h"
#include "Widget/OptionWidget.h"

#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("ContinueGame"));
		ContinueButton->OnClicked.Add(ScriptDelegate);
	}

	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("NewStartGame"));
		NewStartButton->OnClicked.Add(ScriptDelegate);
	}

	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("OpenOption"));
		OptionButton->OnClicked.Add(ScriptDelegate);
	}

	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("QuitGame"));
		QuitButton->OnClicked.Add(ScriptDelegate);
	}
}

void UMainMenuWidget::BeginDestroy()
{
	Super::BeginDestroy();
}

void UMainMenuWidget::ContinueGame()
{
}

void UMainMenuWidget::NewStartGame()
{
}

void UMainMenuWidget::OpenOption()
{
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
