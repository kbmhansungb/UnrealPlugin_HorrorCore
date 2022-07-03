// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HorrorEventStruct.generated.h"

class AActor;
class IHorrorItemInterface;
class UHorrorEventCallerComponent;
class UHorrorEventComponent;

/**
 * This is the struct to sent by the horror component to check the condition of the event.
 * 
 * It is based on the sentence structure of the subject verb and object.
 * Verb simplifies to 'do'.
 */
USTRUCT(BlueprintType)
struct HORRORCORE_API FHorrorEventStruct
{
	GENERATED_BODY()

public:
	FHorrorEventStruct() {}
	FHorrorEventStruct(UHorrorEventCallerComponent* Subject, UHorrorEventComponent* Object, const FVector& Origin, const FVector& Direction) 
		: Subject(Subject), Object(Object), Origin(Origin), Direction(Direction)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHorrorEventCallerComponent* Subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHorrorEventComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FHorrorEventDelegate, const FHorrorEventStruct&);