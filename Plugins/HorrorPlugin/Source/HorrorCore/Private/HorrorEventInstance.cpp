// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance.h"

void UHorrorEventInstance::Execute(const FHorrorEventRequired& HorrorEventRequired)
{
	Enter(HorrorEventRequired);
}

bool UHorrorEventInstance::IsItReuseable_Implementation(const FHorrorEventRequired& HorrorEventRequired) 
{ 
	return false; 
}

void UHorrorEventInstance::Enter_Implementation(const FHorrorEventRequired& HorrorEventRequired)
{ 
}

