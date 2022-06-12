// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventInstance.h"
#include "HorrorEventCondition_HaveHorrorItem.generated.h"

class UHorrorItemAsset;

/**
 * 
 */
UCLASS()
class HORROREVENT_API UHorrorEventCondition_HaveHorrorItem : public UHorrorEventCondition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* CompareClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* SpecificObject;

	bool CheckCondition_Implementation(const FHorrorEventRequired& HorrorEventRequired) override;
};
