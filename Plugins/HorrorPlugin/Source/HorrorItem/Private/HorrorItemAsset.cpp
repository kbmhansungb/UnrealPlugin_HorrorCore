// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorItemAsset.h"
#include "GameFramework/Actor.h"
#include "HorrorEventComponent.h"
#include "HorrorEventFunctionLibrary.h"

void UHorrorItemAsset::CallHorrorEvent_Implementation(const FHorrorEventCallStruct& CallStruct)
{
	if (IsValid(CallStruct.CallerComponent) == false)
	{
		return;
	}

	UHorrorEventComponent* HorrorEventComponent = GetHorrorComponent(CallStruct);

	if (IsValid(HorrorEventComponent) == false)
	{
		return;
	}

	CallStruct.CallerComponent->CallHorrorEvent(HorrorEventComponent);
}

UHorrorEventComponent* UHorrorItemAsset::GetHorrorComponent_Implementation(const FHorrorEventCallStruct& CallStruct) const
{
	UHorrorEventComponent* HorrorEventComponent;
	UHorrorEventFunctionLibrary::GetHorrorEventComponent(
		CallStruct,
		MaximumInteractableDistance,
		HorrorEventComponent);
	return HorrorEventComponent;
}
