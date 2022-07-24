// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HorrorEventStruct.h"
#include "HorrorEventInstance.generated.h"

/**
* In the basic planning of Horror Event, there is only the execution of the event in one direction and the reaction accordingly.
 */
UCLASS(Abstract, ClassGroup = (HorrorEvent), Blueprintable, DefaultToInstanced, EditInlineNew)
class HORRORCORE_API UHorrorEventInstance : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void CallHorrorEvent(const FHorrorEventStruct& HorrorEventRequired);
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) {}
};