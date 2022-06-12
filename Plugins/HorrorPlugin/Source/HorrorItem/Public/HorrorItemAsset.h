// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HorrorItemAsset.generated.h"

class UHorrorEventComponent;
class UHorrorEventCallerComponent;

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
	void CallHorrorEvent(UHorrorEventCallerComponent* CallerComponent) const;
	virtual void CallHorrorEvent_Implementation(UHorrorEventCallerComponent* CallerComponent) const;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UHorrorEventComponent* GetHorrorComponent(UHorrorEventCallerComponent* CallerComponent) const;
	virtual UHorrorEventComponent* GetHorrorComponent_Implementation(UHorrorEventCallerComponent* CallerComponent) const;
};