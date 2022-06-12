// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventInstance.h"
#include "Components/ActorComponent.h"
#include "HorrorEventCallerComponent.generated.h"

class UHorrorEventComponent;
class UHorrorEventCallerComponent;


USTRUCT(BlueprintType)
struct FHorrorEventCallStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHorrorEventCallerComponent* CallerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;
};

UINTERFACE(MinimalAPI, BlueprintType)
class UHorrorItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class HORRORCORE_API IHorrorItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UHorrorEventComponent* GetHorrorComponent(const FHorrorEventCallStruct& CallStruct) const;
	virtual UHorrorEventComponent* GetHorrorComponent_Implementation(const FHorrorEventCallStruct& CallStruct) const { return nullptr; };
};

/**
 * Purpose : Used to call a horror event that can be RPC function using a character or player controller.
 */
UCLASS( ClassGroup=(HorrorEvent), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorEventCallerComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	FHorrorEventRequired GetRequired();

	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	void CallHorrorEvent(const FVector& Origin, const FVector& Direction, TScriptInterface<IHorrorItemInterface> ItemInterface);

protected:
	void ExecuteHorrorEvent(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC_CallHorrorEvent(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
	bool ServerRPC_CallHorrorEvent_Validate(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
	void ServerRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_CallHorrorEvent(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);
	void MulticastRPC_CallHorrorEvent_Implementation(const FHorrorEventRequired& Required, const FHorrorEventInstanced& HorrorEvent);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DefaultRayMaxLength = 200.0f;
};