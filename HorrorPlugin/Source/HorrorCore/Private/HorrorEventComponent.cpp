// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventComponent.h"
#include "GameFramework/Actor.h"

void UHorrorEventComponent::ExecuteHorrorEvent(const FHorrorEventStruct& Required)
{
	for (UHorrorEventCondition* Condition : Conditions)
	{
		if (Condition->IsItCallable(Required) == false)
		{
			return;
		}
	}

	for (UHorrorEventInstance* Event : Events)
	{
		Event->CallHorrorEvent(Required);
	}

	ExecuteHorrorEventDelegate(Required);
}
void UHorrorEventComponent::ExecuteHorrorEventDelegate(const FHorrorEventStruct& Requried)
{
	if (HorrorEventDelegate.IsBound())
	{
		HorrorEventDelegate.Broadcast(Requried);
	}
}

void UHorrorEventComponent::BeginPlay()
{
	Super::BeginPlay();
}
