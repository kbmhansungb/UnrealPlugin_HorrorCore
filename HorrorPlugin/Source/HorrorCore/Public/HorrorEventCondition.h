// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HorrorEventStruct.h"
#include "HorrorEventCondition.generated.h"

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (HorrorEvent), Blueprintable, DefaultToInstanced, EditInlineNew)
class HORRORCORE_API UHorrorEventCondition : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	bool IsItCallable(const FHorrorEventStruct& HorrorEventRequired);
	virtual bool IsItCallable_Implementation(const FHorrorEventStruct& HorrorEventRequired);
};
