// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance.h"

bool UHorrorEventInstance::IsExecuteable(const FHorrorEventRequired& HorrorEventRequired)
{
	return
		State.IsExecuteable() &&
		IsValid(EventCondition) && EventCondition->CheckCondition(HorrorEventRequired);
}

void UHorrorEventInstance::Execute(const FHorrorEventRequired& HorrorEventRequired)
{
	Enter(HorrorEventRequired);

	State.Disabled = !IsItReuseable_Implementation(HorrorEventRequired);
}

bool UHorrorEventInstance::IsItReuseable_Implementation(const FHorrorEventRequired& HorrorEventRequired)
{ 
	return false; 
}

void UHorrorEventInstance::Enter_Implementation(const FHorrorEventRequired& HorrorEventRequired)
{ 
}

