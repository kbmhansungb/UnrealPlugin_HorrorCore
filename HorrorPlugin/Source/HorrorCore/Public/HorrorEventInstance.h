// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventStruct.h"
#include "HorrorEventObjectInterface.h"
#include "HorrorEventInstance.generated.h"

/**
 * In the basic planning of Horror Event, there is only the execution of the event in one direction and the reaction accordingly.
 */
UCLASS(Abstract, ClassGroup = (HorrorEvent), Blueprintable, DefaultToInstanced, EditInlineNew)
class HORRORCORE_API UHorrorEventInstance : public UObject
	, public IHorrorEventObjectInterface
{
	GENERATED_BODY()

public:
	virtual bool IsExecuteable_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
	virtual bool IsLocalEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;

	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct HORRORCORE_API FHorrorEventInstanced
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UHorrorEventInstance* Instance;
};