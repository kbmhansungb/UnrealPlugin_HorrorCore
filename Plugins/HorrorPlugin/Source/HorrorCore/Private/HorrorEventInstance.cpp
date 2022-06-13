// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance.h"

bool UHorrorEventInstance::IsExecuteable(const FHorrorEventStruct& HorrorEventRequired)
{
	return
		State.Disabled == false &&
		(IsValid(EventCondition) ? EventCondition->CheckCondition(HorrorEventRequired) : true);
}

void UHorrorEventInstance::Execute(const FHorrorEventStruct& HorrorEventRequired)
{
	Enter(HorrorEventRequired);

	State.Disabled = !IsItReuseable_Implementation(HorrorEventRequired);
}

bool UHorrorEventInstance::IsItReuseable_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{ 
	return false; 
}

void UHorrorEventInstance::Enter_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{ 
}

FHorrorEventStruct::FHorrorEventStruct() {}

FHorrorEventStruct::FHorrorEventStruct(AActor* Subject, AActor* Object, TScriptInterface<IHorrorItemInterface> ItemInterface, FVector Origin, FVector Direction)
	: Subject(Subject), Object(Object), ItemInterface(ItemInterface), Origin(Origin), Direction(Direction)
{
}
