// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorEventInstance.h"
#include "HorrorEventInstance_Sequence.generated.h"

class AActor;
class ALevelSequenceActor;
class UActorSequenceComponent;

/*
 * It is intended to be implemented in actors that call HorrorEvent.
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UHorrorSequenceInterface : public UInterface
{
	GENERATED_BODY()
};

class IHorrorSequenceInterface
{
	GENERATED_BODY()

public:
	/** Add interface function declarations here */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlaySequence(const FHorrorEventStruct& HorrorEventRequired);
	virtual void PlaySequence_Implementation(const FHorrorEventStruct& HorrorEventRequired) {};
};

#pragma region Events

UCLASS()
class HORROREVENT_API UHorrorEventInstance_PlaySequence : public UHorrorEventInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "HorrorEvent", EditAnywhere, BlueprintReadWrite)
	AActor* SequenceActor;

	UPROPERTY(Category = "HorrorEvent", EditAnywhere, BlueprintReadWrite)
	FName SequenceTag;

	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};

#pragma endregion