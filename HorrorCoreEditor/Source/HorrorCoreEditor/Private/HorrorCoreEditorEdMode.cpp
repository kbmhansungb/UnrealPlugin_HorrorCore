// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorCoreEditorEdMode.h"
#include "HorrorCoreEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FHorrorCoreEditorEdMode::EM_HorrorCoreEditorEdModeId = TEXT("EM_HorrorCoreEditorEdMode");

FHorrorCoreEditorEdMode::FHorrorCoreEditorEdMode()
{

}

FHorrorCoreEditorEdMode::~FHorrorCoreEditorEdMode()
{

}

void FHorrorCoreEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FHorrorCoreEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FHorrorCoreEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FHorrorCoreEditorEdMode::UsesToolkits() const
{
	return true;
}




