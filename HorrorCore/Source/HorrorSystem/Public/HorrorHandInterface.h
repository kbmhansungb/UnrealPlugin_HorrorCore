// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <Engine/EngineTypes.h>
#include "HorrorHandInterface.generated.h"

class IHorrorHoldableInterface;

UINTERFACE(MinimalAPI, BlueprintType)
class UHorrorHandInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORSYSTEM_API IHorrorHandInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void GetHoldItem(bool& IsHold, TScriptInterface<IHorrorHoldableInterface>& HoldableItem) const;
	virtual void GetHoldItem_Implementation(bool& IsHold, TScriptInterface<IHorrorHoldableInterface>& HoldableItem) const = 0;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IHorrorHoldableInterface> GetHoldable() const;
	virtual TScriptInterface<IHorrorHoldableInterface> GetHoldable_Implementation() const = 0;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void GetHoldablePutLocation(FHitResult& HitResult) const;
	virtual void GetHoldablePutLocation_Implementation(FHitResult& HitResult) const = 0;
};
