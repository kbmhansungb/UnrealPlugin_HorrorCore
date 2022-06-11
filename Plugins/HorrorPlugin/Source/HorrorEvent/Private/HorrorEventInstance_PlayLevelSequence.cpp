// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance_PlayLevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void UHorrorEventInstance_PlayLevelSequence::Enter_Implementation(const FHorrorEventRequired& HorrorEventRequired)
{
	if ( !LevelSequenceActor )
	{
		return;
	}

	LevelSequenceActor->GetSequencePlayer()->Play();
}
