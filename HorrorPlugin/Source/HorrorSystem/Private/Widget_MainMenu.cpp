// 2022 06    Bum moo, Kim    Free copyright


#include "Widget_MainMenu.h"
#include "Components/Button.h"
#include "HorrorSystem/Public/Widget_Option.h"

#include "Kismet/GameplayStatics.h"

void UWidget_MainMenu::NativePreConstruct()
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

void UWidget_MainMenu::BeginDestroy()
{
	Super::BeginDestroy();
}

void UWidget_MainMenu::ContinueGame()
{
}

void UWidget_MainMenu::NewStartGame()
{
}

void UWidget_MainMenu::OpenOption()
{
}

void UWidget_MainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
