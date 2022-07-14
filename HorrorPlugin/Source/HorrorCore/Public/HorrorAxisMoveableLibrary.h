// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HorrorAxisMoveableInterface.h"
#include "HorrorAxisMoveableLibrary.generated.h"

class USceneComponent;

/**
 * 
 */
UCLASS()
class HORRORCORE_API UHorrorAxisMoveableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = "Horror", BlueprintCallable)
	static void InputAxisMovement(USceneComponent* Component, const FVector2D& MouseMovement, bool MeetMoveableInterface = true);

	UFUNCTION(Category = "Horror", BlueprintCallable)
	static void SearchMovealbeInterfaces(USceneComponent* Component, bool MeetMoveableInterface, TArray<TScriptInterface<IHorrorAxisMoveableInterface>>& MoveableInterfaces, USceneComponent*& SceneComponent);

	UFUNCTION(Category = "Horror", BlueprintCallable)
	static void InputAxisMovementTo(const TScriptInterface<IHorrorAxisMoveableInterface>& MoveableInterfaces, USceneComponent* SceneComponent, const FVector2D& MouseMovement);
};
