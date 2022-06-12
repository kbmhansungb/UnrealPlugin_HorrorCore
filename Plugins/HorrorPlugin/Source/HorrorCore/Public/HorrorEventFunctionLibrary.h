// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HorrorEventCallerComponent.h"
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
	static void GetHorrorEventComponent(const FHorrorEventCallStruct& CallStruct, float Length, UHorrorEventComponent*& HorrorEventComponent);

	/**
	 *  For example returns the Actor closest to collision in the traced range when a picture was taken with the camera.
	 */
	UFUNCTION(BlueprintCallable, Category = "HorrorEvent")
	static void GetHorrorEventComponentLikeEye(const FHorrorEventCallStruct& CallStruct, float Length, float Radius, UHorrorEventComponent*& HorrorEventComponent);
};
