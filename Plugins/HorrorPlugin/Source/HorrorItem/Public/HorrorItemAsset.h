// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HorrorEventCallerComponent.h"
#include "HorrorItemAsset.generated.h"

class UHorrorEventComponent;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class HORRORITEM_API UHorrorItemAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaximumInteractableDistance = 300.f;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CallHorrorEvent(const FHorrorEventCallStruct& CallStruct);
	virtual void CallHorrorEvent_Implementation(const FHorrorEventCallStruct& CallStruct);

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UHorrorEventComponent* GetHorrorComponent(const FHorrorEventCallStruct& CallStruct) const;
	virtual UHorrorEventComponent* GetHorrorComponent_Implementation(const FHorrorEventCallStruct& CallStruct) const;
};