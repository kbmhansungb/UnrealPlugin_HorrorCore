// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance.h"

bool UHorrorEventInstance::IsExecuteable_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	return true;
}

bool UHorrorEventInstance::IsLocalEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	return false;
}

void UHorrorEventInstance::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
}

