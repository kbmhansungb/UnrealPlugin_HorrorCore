// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HorrorEventInstance.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct HORRORCORE_API FHorrorEventRequired
{
	GENERATED_BODY()

public:
	FHorrorEventRequired() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<class AActor> Subject;
};

/**
 * In the basic planning of Horror Event, there is only the execution of the event in one direction and the reaction accordingly.
 */
UCLASS(Abstract, ClassGroup = (HorrorEvent), Blueprintable, DefaultToInstanced, EditInlineNew)
class HORRORCORE_API UHorrorEventInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorrorEvent")
	void CallHorrorEvent(const FHorrorEventRequired& HorrorEventRequired);
	virtual void CallHorrorEvent_Implementation(const FHorrorEventRequired& HorrorEventRequired) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDisable;
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
	TArray<UHorrorEventInstance*> Instances;
};