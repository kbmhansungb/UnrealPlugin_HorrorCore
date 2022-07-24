// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorEventInstance.h"
#include "HorrorEventCondition.h"
#include "HorrorEventComponent.generated.h"

struct FHorrorEventStruct;

DECLARE_MULTICAST_DELEGATE_OneParam(FHorrorEventDelegate, const FHorrorEventStruct&);

/**
 *
 */
UCLASS( ClassGroup=(HorrorEvent), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorEventComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Horror", BlueprintCallable)
	void ExecuteHorrorEvent(const FHorrorEventStruct& Required);

	UFUNCTION(Category = "Horror", BlueprintCallable)
	bool BindHorrorEvent(UHorrorEventComponent* HorrorEventComponent);

	UFUNCTION(Category = "Horror", BlueprintCallable)
	void UnbindHorrorEvent(UHorrorEventComponent* HorrorEventComponent);

private:
	FHorrorEventDelegate HorrorEventDelegate;
	FDelegateHandle DelegateHandle;

	void ExecuteHorrorEventDelegate(const FHorrorEventStruct& Requried);

protected:
	UPROPERTY(Category = "Horror", Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<UHorrorEventCondition*> Conditions;

	UPROPERTY(Category = "Horror", Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<UHorrorEventInstance*> Events;

public:
	virtual void BeginPlay() override;
};