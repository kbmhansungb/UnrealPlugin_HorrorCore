// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventInstance.h"
#include "Components/ActorComponent.h"
#include "HorrorEventCallerComponent.generated.h"

class AActor;
class UHorrorEventComponent;
class UHorrorEventCallerComponent;

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
};

/**
 * Purpose : Used to call a horror event that can be RPC function using a character or player controller.
 */
UCLASS( ClassGroup=(HorrorEvent), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorEventCallerComponent final : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HorrorEvent")
	TScriptInterface<IHorrorItemInterface> ItemInterface;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorrorEventCallSetting")
	bool IsCallActor = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorrorEventCallSetting")
	bool IsCallComponent = true;

public:
	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	void CallHorrorEvent(const FVector& Origin, const FVector& Direction);

protected:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC_MulticastHorrorEvent(AActor* Actor, const FHorrorEventStruct& Required);
	bool ServerRPC_MulticastHorrorEvent_Validate(AActor* Actor, const FHorrorEventStruct& Required);
	void ServerRPC_MulticastHorrorEvent_Implementation(AActor* Actor, const FHorrorEventStruct& Required);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_CallHorrorEvent(AActor* Actor, const FHorrorEventStruct& Required);
	void MulticastRPC_CallHorrorEvent_Implementation(AActor* Actor, const FHorrorEventStruct& Required);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RayMaxLength = 200.0f;
};