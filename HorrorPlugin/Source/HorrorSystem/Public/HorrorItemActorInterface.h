// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorItemActorInterface.generated.h"

class IHorrorItemInterface;
class UHorrorHandComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHorrorItemActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORSYSTEM_API IHorrorItemActorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	TScriptInterface<IHorrorItemInterface> GetItemInterface();
	virtual TScriptInterface<IHorrorItemInterface> GetItemInterface_Implementation() { return TScriptInterface<IHorrorItemInterface>(); }
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	bool IsHoldable(UHorrorHandComponent* HandComponent);
	virtual bool IsHoldable_Implementation(UHorrorHandComponent* HandComponent);

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	void DoHold(UHorrorHandComponent* HandComponent);
	virtual void DoHold_Implementation(UHorrorHandComponent* HandComponent) {}
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	void DoPut(UHorrorHandComponent* HandComponent);
	virtual void DoPut_Implementation(UHorrorHandComponent* HandComponent) {}

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	void PutWorld();
	virtual void PutWorld_Implementation() {};
};
