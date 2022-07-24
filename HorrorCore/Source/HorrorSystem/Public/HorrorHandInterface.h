// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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
	bool IsDominanceHand() const;
	virtual bool IsDominanceHand_Implementation() const { return false; }

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IHorrorHoldableInterface> GetHoldable() const;
	virtual TScriptInterface<IHorrorHoldableInterface> GetHoldable_Implementation() const;
};
