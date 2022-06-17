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
	TWeakObjectPtr<ALevelSequenceActor> LevelSequenceActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsExecutable = true;

public:
	virtual bool IsExecuteable_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};
