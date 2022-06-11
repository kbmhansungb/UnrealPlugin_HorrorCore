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
 *  This Struct is defined for the purpose of saving.
 */
USTRUCT(BlueprintType)
struct HORRORCORE_API FHorrorEventState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Disabled;

	FORCEINLINE bool IsExecuteable() const { return !Disabled; }
};

/**
 * In the basic planning of Horror Event, there is only the execution of the event in one direction and the reaction accordingly.
 */
UCLASS(Abstract, ClassGroup = (HorrorEvent), Blueprintable, DefaultToInstanced, EditInlineNew)
class HORRORCORE_API UHorrorEventInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHorrorEventState State;

protected:
	/**
	 *  Used to net multicast from Horror Event Caller Component.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool LocalEvent = false;
public:
	FORCEINLINE bool IsLocalEvent() const { return LocalEvent; }

public:
	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	void Execute(const FHorrorEventRequired& HorrorEventRequired);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorrorEvent")
	bool IsItReuseable(const FHorrorEventRequired& HorrorEventRequired);
	virtual bool IsItReuseable_Implementation(const FHorrorEventRequired& HorrorEventRequired);

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorrorEvent")
	void Enter(const FHorrorEventRequired& HorrorEventRequired);
	virtual void Enter_Implementation(const FHorrorEventRequired& HorrorEventRequired);
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