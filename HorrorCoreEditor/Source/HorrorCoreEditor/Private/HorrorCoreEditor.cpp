// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorCoreEditor.h"
#include "HorrorCoreEditorEdMode.h"

#define LOCTEXT_NAMESPACE "FHorrorCoreEditorModule"

void FHorrorCoreEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FHorrorCoreEditorEdMode>(FHorrorCoreEditorEdMode::EM_HorrorCoreEditorEdModeId, LOCTEXT("HorrorCoreEditorEdModeName", "HorrorCoreEditorEdMode"), FSlateIcon(), true);
}

void FHorrorCoreEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FHorrorCoreEditorEdMode::EM_HorrorCoreEditorEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHorrorCoreEditorModule, HorrorCoreEditor)