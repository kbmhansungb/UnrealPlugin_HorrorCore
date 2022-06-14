// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HorrorEventStruct.generated.h"

class AActor;
class IHorrorItemInterface;

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
	FHorrorEventStruct(AActor* Subject, AActor* Object, TScriptInterface<IHorrorItemInterface> ItemInterface, FVector Origin, FVector Direction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<IHorrorItemInterface> ItemInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;
};