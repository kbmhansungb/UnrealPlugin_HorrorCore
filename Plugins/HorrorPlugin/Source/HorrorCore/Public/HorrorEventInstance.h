// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HorrorEventInstance.generated.h"

class AActor;
class IHorrorItemInterface;

/**
 * Purpose : This is the struct to sent by the horror component to check the condition of the event.
 * 
 * It is based on the sentence structure of the subject verb and object.
 * Verb simplifies to 'do'.
 */
USTRUCT(BlueprintType)
struct HORRORCORE_API FHorrorEventStruct
{
	GENERATED_BODY()

public:
	FHorrorEventStruct();
	FHorrorEventStruct(AActor* Subject, AActor* Object, TScriptInterface<IHorrorItemInterface> ItemInterface, FVector Origin, FVector Direction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<IHorrorItemInterface> ItemInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;
};

/**
 *  This Struct is defined for the purpose of saving.
 */
USTRUCT(BlueprintType)
struct HORRORCORE_API FHorrorEventState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Disabled;
};

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (HorrorEvent), Blueprintable, DefaultToInstanced, EditInlineNew)
class HORRORCORE_API UHorrorEventCondition : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CheckCondition(const FHorrorEventStruct& HorrorEventRequired);
	virtual bool CheckCondition_Implementation(const FHorrorEventStruct& HorrorEventRequired) { return true; };
};

/**
 * In the basic planning of Horror Event, there is only the execution of the event in one direction and the reaction accordingly.
 */
UCLASS(Abstract, ClassGroup = (HorrorEvent), Blueprintable, DefaultToInstanced, EditInlineNew)
class HORRORCORE_API UHorrorEventInstance : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool IsExecuteable(const FHorrorEventStruct& HorrorEventRequired);

	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	void Execute(const FHorrorEventStruct& HorrorEventRequired);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHorrorEventState State;
//public:
//	FORCEINLINE const FHorrorEventState& GetState() const { return State; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "HorrorEventDefinition")
	UHorrorEventCondition* EventCondition;

	/**
	 *  Used to net multicast from Horror Event Caller Component.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HorrorEventDefinition")
	bool LocalEvent = false;
public:
	FORCEINLINE bool IsLocalEvent() const { return LocalEvent; }
	
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorrorEvent")
	bool IsItReuseable(const FHorrorEventStruct& HorrorEventRequired);
	virtual bool IsItReuseable_Implementation(const FHorrorEventStruct& HorrorEventRequired);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorrorEvent")
	void Enter(const FHorrorEventStruct& HorrorEventRequired);
	virtual void Enter_Implementation(const FHorrorEventStruct& HorrorEventRequired);
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