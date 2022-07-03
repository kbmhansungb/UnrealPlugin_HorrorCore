// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventStruct.h"
#include "HorrorEventInstance.h"
#include "Components/ActorComponent.h"
#include "HorrorEventComponent.generated.h"

/**
 *
 */
UCLASS( ClassGroup=(HorrorEvent), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorEventComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Horror")
	void ExecuteHorrorEvent(const FHorrorEventStruct& Required);

public:
	FHorrorEventDelegate HorrorEventDelegate;
protected:
	void ExecuteHorrorEventDelegate(const FHorrorEventStruct& Requried);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Horror")
	TArray<FHorrorEventInstanced> HorrorEvents;

public:
	virtual void BeginPlay() override;
};