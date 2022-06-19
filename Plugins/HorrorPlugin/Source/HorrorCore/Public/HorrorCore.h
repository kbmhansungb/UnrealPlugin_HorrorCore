// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "HAL/IConsoleManager.h"

class FHorrorCoreModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(HorrorEventLog, Log, All);

#if !NO_CVARS

extern TAutoConsoleVariable<bool> CVar_HorrorEvent_DebugDraw(TEXT("HorrorEvent.DebugDraw"), false, TEXT("Debug draw horror events."), ECVF_Default);

#endif
