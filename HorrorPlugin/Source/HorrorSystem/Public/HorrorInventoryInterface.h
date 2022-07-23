// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorItemInterface.h"
#include "HorrorInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UHorrorInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORSYSTEM_API IHorrorInventoryInterface
{
	GENERATED_BODY()

public:
	virtual bool IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const = 0;
	virtual void StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) = 0;
	
	virtual bool IsTakable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const = 0;
	virtual const TScriptInterface<IHorrorItemInterface>& TakeItem(FIntPoint Index) = 0;

	virtual const FIntSize2D& GetInventorySize() const = 0;
};