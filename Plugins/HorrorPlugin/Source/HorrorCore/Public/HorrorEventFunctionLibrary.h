// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HorrorEventFunctionLibrary.generated.h"

class UHorrorEventComponent;

UCLASS()
class HORRORCORE_API UHorrorEventFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 *  Return a horror component for the first hit collision that the result of line traced
	 */
	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	static void GetHorrorEventComponent(AActor* Actor, const FVector& Start, const FVector& Direction, float Length, UHorrorEventComponent*& HorrorEventComponent);

	/**
	 *  For example returns the Actor closest to collision in the traced range when a picture was taken with the camera.
	 */
	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	static void GetHorrorEventComponentLikeEye(AActor* Actor, const FVector& Start, const FVector& Direction, float Length, float Radius, UHorrorEventComponent*& HorrorEventComponent);
};
