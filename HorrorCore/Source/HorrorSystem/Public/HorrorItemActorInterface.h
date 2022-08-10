// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorItemActorInterface.generated.h"

class IHorrorItemInterface;
class UHorrorHandComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
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
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void GetItemInterface(TScriptInterface<IHorrorItemInterface>& ItemInterface);
	virtual void GetItemInterface_Implementation(TScriptInterface<IHorrorItemInterface>& ItemInterface) = 0;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void HoldItemActor(UHorrorHandComponent* HandComponent);
	virtual void HoldItemActor_Implementation(UHorrorHandComponent* HandComponent) = 0;
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void ReleaseItemActor(UHorrorHandComponent* HandComponent);
	virtual void ReleaseItemActor_Implementation(UHorrorHandComponent* HandComponent) = 0;
};
