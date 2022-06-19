// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorCore.h"

#define LOCTEXT_NAMESPACE "FHorrorCoreModule"

void FHorrorCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FHorrorCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHorrorCoreModule, HorrorCore)


DEFINE_LOG_CATEGORY(HorrorEventLog);


#if !NO_CVARS

FAutoConsoleCommand CCmd_HorrorEvent_PrintConsoleState(
    TEXT("HorrorEvent.PrintConsoleState"),
    TEXT("Print HorrorEvent`s Consol state."),
    FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Params)
        {
            UE_LOG(HorrorEventLog, Display, TEXT("DebugDraw : %s"), CVar_HorrorEvent_DebugDraw.GetValueOnGameThread() ? TEXT("true") : TEXT("false"));
        }),
    ECVF_Default);

#endif