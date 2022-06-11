// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventInstance.h"
#include "Components/ActorComponent.h"
#include "HorrorEventCallerComponent.generated.h"

class UHorrorEventComponent;

UCLASS( ClassGroup=(HorrorEvent), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorEventCallerComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CallHorrorEvent(UHorrorEventComponent* HorrorEventComponent);

protected:
	void ExecuteHorrorEvent(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);

	UFUNCTION(Server, Reliable)
	void ServerRPC_CallHorrorEvent(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
	bool ServerRPC_CallHorrorEvent_Validate(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
	void ServerRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_CallHorrorEvent(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
	bool MulticastRPC_CallHorrorEvent_Validate(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
	void MulticastRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
};
