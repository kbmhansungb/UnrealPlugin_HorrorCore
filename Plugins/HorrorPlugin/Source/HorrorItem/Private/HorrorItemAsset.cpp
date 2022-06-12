// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorItemAsset.h"
#include "GameFramework/Actor.h"
#include "HorrorEventComponent.h"
#include "HorrorEventCallerComponent.h"
#include "HorrorEventFunctionLibrary.h"

void UHorrorItemAsset::CallHorrorEvent_Implementation(UHorrorEventCallerComponent* CallerComponent) const
{
	UHorrorEventComponent* HorrorEventComponent = GetHorrorComponent(CallerComponent);

	if (IsValid(HorrorEventComponent) == false)
	{
		return;
	}

	CallerComponent->CallHorrorEvent(HorrorEventComponent);
}

UHorrorEventComponent* UHorrorItemAsset::GetHorrorComponent_Implementation(UHorrorEventCallerComponent* CallerComponent) const
{
	AActor* Owner = CallerComponent->GetOwner();
	UHorrorEventComponent* HorrorEventComponent;
	UHorrorEventFunctionLibrary::GetHorrorEventComponent(
		Owner,
		Owner->GetActorTransform().GetLocation(),
		Owner->GetActorForwardVector(),
		MaximumInteractableDistance,
		HorrorEventComponent);
	return HorrorEventComponent;
}
