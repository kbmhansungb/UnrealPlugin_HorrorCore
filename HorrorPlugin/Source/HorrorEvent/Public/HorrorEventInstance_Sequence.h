// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "HorrorEventInstance.h"
#include "HorrorEventInstance_Sequence.generated.h"

class ALevelSequenceActor;

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
	void PlaySequence(FName SequenceName);
	virtual void PlaySequence_Implementation(FName SequenceName) {};
};

#pragma region HorrorSequenceActor

UCLASS(ClassGroup = (Horror), BlueprintType, Blueprintable)
class HORROREVENT_API AHorrorSequence : public AActor
	, public IHorrorSequenceInterface
{
	GENERATED_BODY()

public:
};

#pragma endregion

#pragma region Events

/**
 *
 */
UCLASS()
class HORROREVENT_API UHorrorEventInstance_PlayLevelSequence : public UHorrorEventInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "HorrorEvent", EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<ALevelSequenceActor> LevelSequenceActor;

	UPROPERTY(Category = "HorrorEvent", EditAnywhere, BlueprintReadWrite)
	bool IsExecutable = true;

public:
	virtual bool IsExecuteable_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};

/**
 *
 */
UCLASS()
class HORROREVENT_API UHorrorEventInstance_PlayHorrorSequence : public UHorrorEventInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "HorrorEvent", EditAnywhere, BlueprintReadWrite)
	TScriptInterface<IHorrorSequenceInterface> HorrorSequenceActor;

	UPROPERTY(Category = "HorrorEvent", EditAnywhere, BlueprintReadWrite)
	FName SequenceName;

public:
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};


#pragma endregion