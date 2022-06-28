// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorEventStruct.h"
#include "HorrorEventObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHorrorEventObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORCORE_API IHorrorEventObjectInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool IsExecuteable(const FHorrorEventStruct& Required);
	virtual bool IsExecuteable_Implementation(const FHorrorEventStruct& Required);

	UFUNCTION(BlueprintNativeEvent)
	void CallHorrorEvent(const FHorrorEventStruct& Required);
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& Required);
};
