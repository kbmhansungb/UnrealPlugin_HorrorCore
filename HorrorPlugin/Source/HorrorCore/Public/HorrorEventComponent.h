// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorrorEvent")
	TArray<FHorrorEventInstanced> HorrorEvents;
public:
	FORCEINLINE TArray<FHorrorEventInstanced>& GetHorrorEvents() { return HorrorEvents; };
};