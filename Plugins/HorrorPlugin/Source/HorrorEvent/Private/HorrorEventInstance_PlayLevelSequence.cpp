// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance_PlayLevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

bool UHorrorEventInstance_PlayLevelSequence::IsExecuteable_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	return IsExecutable;
}

void UHorrorEventInstance_PlayLevelSequence::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	IsExecutable = false;

	if (LevelSequenceActor.IsValid() == false)
	{
		return;
	}

	LevelSequenceActor->GetSequencePlayer()->Play();
}
