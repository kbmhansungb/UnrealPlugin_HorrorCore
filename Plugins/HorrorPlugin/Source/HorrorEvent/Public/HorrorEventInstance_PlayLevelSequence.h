// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventInstance.h"
#include "HorrorEventInstance_PlayLevelSequence.generated.h"

class ALevelSequenceActor;

/**
 * 
 */
UCLASS()
class HORROREVENT_API UHorrorEventInstance_PlayLevelSequence : public UHorrorEventInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALevelSequenceActor* LevelSequenceActor;

public:
	virtual void Enter_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};
