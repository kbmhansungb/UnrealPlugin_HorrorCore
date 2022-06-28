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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorrorEvent")
	bool BindActorOverlapEvent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorrorEvent")
	bool BindActorEndEvent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorrorEvent")
	TArray<FHorrorEventInstanced> HorrorEvents;

public:
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_CallHorrorEvent(const FHorrorEventStruct& Required);
	void Multicast_CallHorrorEvent_Implementation(const FHorrorEventStruct& Required);
};