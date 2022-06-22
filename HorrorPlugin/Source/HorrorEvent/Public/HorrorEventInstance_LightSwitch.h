// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/ActorComponent.h"
#include "HorrorEventInstance.h"
#include "GameFramework/Actor.h"
#include "HorrorEventInstance_LightSwitch.generated.h"

class ALight;

USTRUCT(BlueprintType)
struct FHorrorLIghtStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Intensity = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALight*	Light;
};

UCLASS(ClassGroup = (Horror), BlueprintType, Blueprintable)
class UHorrorLightComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Light", EditAnywhere, BlueprintReadWrite)
	bool IsBroke;

	UPROPERTY(Category = "Light", EditAnywhere, BlueprintReadWrite)
	bool IsUnstable;
	
	UPROPERTY(Category = "Light", EditAnywhere, BlueprintReadWrite)
	bool IsOn;

	UPROPERTY(Category = "Lights", EditAnywhere, BlueprintReadWrite)
	float MultiflyIntensity = 1.0f;

	UPROPERTY(Category = "Lights", EditAnywhere, BlueprintReadWrite)
	FLinearColor BaseColor = FLinearColor::White;

	UPROPERTY(Category = "Lights", EditAnywhere, BlueprintReadWrite)
	TArray<FHorrorLIghtStruct> Lights;

public:
	FORCEINLINE bool DoesItTurnOn(bool NewOn) const
	{
		return ((IsBroke == false) && NewOn);
	}
	FORCEINLINE bool DoesItShine() const
	{
		return (MultiflyIntensity) > 0.f && (BaseColor != BaseColor.Black);
	}
public:
	UFUNCTION(BlueprintCallable)
	void SetState(bool NewOn);

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateLight();
};


/*
 * It is intended to be implemented in actors that call HorrorEvent.
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UHorrorLightInterface : public UInterface
{
	GENERATED_BODY()
};

class IHorrorLightInterface
{
	GENERATED_BODY()

public:
	/** Add interface function declarations here */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetLight(bool NewOn);
	virtual void SetLight_Implementation(bool NewOn) {};
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SwitchLight();
	virtual void SwitchLight_Implementation() {};
};

#pragma region HorrorLightActor
/**
 * HorrorComponent and the use of the Light interface. It can be inherited or implemented in any actor you want to use.
 */
UCLASS(ClassGroup = (Horror), BlueprintType, Blueprintable)
class AHorrorLight : public AActor
	, public IHorrorLightInterface
{
	GENERATED_BODY()

public:
	AHorrorLight();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHorrorLightComponent* HorrorLightComponent;

public:
	virtual void SetLight_Implementation(bool NewOn) override;
	virtual void SwitchLight_Implementation() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PostSetLightState();
};

#pragma endregion

#pragma region HorrorEvents

/*
 * Switch light.
 */
UCLASS()
class HORROREVENT_API UHorrorEventInstance_LightSwitch : public UHorrorEventInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<UHorrorLightInterface> HorrorLightActor;

public:
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};

#pragma endregion