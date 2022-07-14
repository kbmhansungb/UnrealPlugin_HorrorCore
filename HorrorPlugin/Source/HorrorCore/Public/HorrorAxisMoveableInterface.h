// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorAxisMoveableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHorrorAxisMoveableInterface : public UInterface
{
	GENERATED_BODY()
};

class HORRORCORE_API IHorrorAxisMoveableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void ApplyAxisMovealbe(USceneComponent* Target, const FVector2D& MouseInput);
	virtual void ApplyAxisMovealbe_Implementation(USceneComponent* Target, const FVector2D& MouseInput);
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void StartAxisMovealbe(USceneComponent* Target);
	virtual void StartAxisMovealbe_Implementation(USceneComponent* Target) {}

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void EndAxisMovealbe(USceneComponent* Target);
	virtual void EndAxisMovealbe_Implementation(USceneComponent* Target) {}
};
