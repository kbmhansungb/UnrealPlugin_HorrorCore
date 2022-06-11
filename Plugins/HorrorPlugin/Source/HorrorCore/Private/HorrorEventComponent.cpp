// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventComponent.h"

// Sets default values for this component's properties
UHorrorEventComponent::UHorrorEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHorrorEventComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHorrorEventComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHorrorEventComponent::CallHorrorEvents(const FHorrorEventRequired& HorrorEventRequired)
{
	for (auto& HorrorEventInstance : HorrorEvent.Instances)
	{
		if ( !HorrorEventInstance )
		{
			continue;
		}

		if ( !HorrorEventInstance->IsDisable )
		{
			HorrorEventInstance->CallHorrorEvent(HorrorEventRequired);
		}
	}
}

