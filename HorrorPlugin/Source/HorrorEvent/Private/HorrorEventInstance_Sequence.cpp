// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance_Sequence.h"
#include "GameFramework/Actor.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

void UHorrorEventInstance_PlaySequence::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	TScriptInterface<UHorrorSequenceInterface> HorrorSequenceInterface;
	if (ALevelSequenceActor * LevelSequenceActor = Cast<ALevelSequenceActor>(SequenceActor))
	{
		LevelSequenceActor->GetSequencePlayer()->Play();
		HorrorSequenceInterface = LevelSequenceActor->GetSequence()->GetDirectorBlueprint();
	}
	else
	{
		TArray<UActorSequenceComponent*> Components;
		SequenceActor->GetComponents<UActorSequenceComponent>(Components);

		UActorSequenceComponent** Component = Components.FindByPredicate(
			[DesireName = SequenceName](const UActorComponent* Component) -> bool
			{
				return Component->GetFName().IsEqual(DesireName);
			}
		);

		if (Component != nullptr)
		{
			(*Component)->GetSequencePlayer()->Play();
		}

		HorrorSequenceInterface = SequenceActor;
	}

	if (HorrorSequenceInterface.GetInterface())
	{
		IHorrorSequenceInterface::Execute_PlaySequence(HorrorSequenceInterface.GetObject(), HorrorEventRequired);
	}
}
