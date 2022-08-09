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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index);
	virtual bool IsStorable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index);
	virtual bool StoreItem_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsTakable(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& ItemInterface) const;
	virtual bool IsTakable_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& ItemInterface) const = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TakeItem(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& ItemInterface);
	virtual bool TakeItem_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& ItemInterface) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetInventorySize(FIntSize2D& InventorySize) const;
	virtual void GetInventorySize_Implementation(FIntSize2D& InventorySize) const = 0;
};