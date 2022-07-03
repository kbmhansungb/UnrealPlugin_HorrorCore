// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorEventInstance_Sequence.h"
#include "GameFramework/Actor.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

void UHorrorEventInstance_PlaySequence::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	if (!SequenceActor)
	{
		return;
	}

	if (ALevelSequenceActor * Sequence = Cast<ALevelSequenceActor>(SequenceActor))
	{
		Sequence->GetSequencePlayer()->Play();
		
		//UBlueprint* Director = Sequence->GetSequence()->GetDirectorBlueprint();
		//if (Director->GetClass()->ImplementsInterface(UHorrorSequenceInterface::StaticClass()))
		//{
		//	IHorrorSequenceInterface::Execute_PlaySequence(Director, HorrorEventRequired);
		//}
	}


	TArray<UActorComponent*> Components = SequenceActor->GetComponentsByTag(UActorSequenceComponent::StaticClass(), SequenceTag);
	for (UActorComponent* Component : Components)
	{
		UActorSequenceComponent* Sequence = Cast<UActorSequenceComponent>(Component);

		Sequence->GetSequencePlayer()->Play();

		//UBlueprint* Director = Sequence->GetSequence()->GetParentBlueprint();
		//if (Director->GetClass()->ImplementsInterface(UHorrorSequenceInterface::StaticClass()))
		//{
		//	IHorrorSequenceInterface::Execute_PlaySequence(Director, HorrorEventRequired);
		//}
	}
}
