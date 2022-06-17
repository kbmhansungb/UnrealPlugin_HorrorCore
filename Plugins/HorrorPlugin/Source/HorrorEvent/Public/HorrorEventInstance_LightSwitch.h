// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "HorrorEventInstance.h"
#include "HorrorEventInstance_LightSwitch.generated.h"

class AActor;
class ULocalLightComponent;

UENUM(BlueprintType)
enum class ELightState : uint8
{
	OFF,
	ON,
	UNSTABLE,
	BROKE,
};

/**
 * Switch work on local lights.
 */
UCLASS()
class HORROREVENT_API UHorrorEventInstance_LightSwitch : public UHorrorEventInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELightState LightState = ELightState::OFF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;

public:
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;

protected:
	/**
	* It works if the outer is a component or an actor.
	*/
	UFUNCTION(Category = "LightSwitch", BlueprintCallable, CallInEditor)
	void UpdateState();
	
	void UpdateComponentsLight(AActor* TargetActor, bool Visibility);
	void UpdateChildActorsLight(AActor* TargetActor, bool Visibility);

	void UpdateLocalLightComponent(ULocalLightComponent* LocalLightComponent, bool Visibility);

	bool IsLightEffectTheWorld();
};
