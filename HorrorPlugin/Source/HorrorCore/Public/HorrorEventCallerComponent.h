// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventInstance.h"
#include "Components/ActorComponent.h"
#include "HorrorEventCallerComponent.generated.h"

class AActor;
class UHorrorEventComponent;
class UHorrorEventCallerComponent;

/**
 * Purpose : Used to call a horror event that can be RPC function using a character or player controller.
 */
UCLASS( ClassGroup=(HorrorEvent), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorEventCallerComponent final : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TraceEventLength = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TraceRadius = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETraceTypeQuery> TraceChannel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TraceComplex = false;

public:
	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	void CallHorrorEvent(const FVector& Origin, const FVector& Direction);

protected:
	virtual void TraceEventComponent(const FVector& Origin, const FVector& Direction, FHitResult& HitResult);

protected:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC_MulticastHorrorEvent(const FHorrorEventStruct& Required);
	bool ServerRPC_MulticastHorrorEvent_Validate(const FHorrorEventStruct& Required);
	void ServerRPC_MulticastHorrorEvent_Implementation(const FHorrorEventStruct& Required);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_CallHorrorEvent(const FHorrorEventStruct& Required);
	void MulticastRPC_CallHorrorEvent_Implementation(const FHorrorEventStruct& Required);
};