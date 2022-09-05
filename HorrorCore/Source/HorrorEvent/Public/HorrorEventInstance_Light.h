// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorEventInstance.h"
#include "HorrorEventInstance_Light.generated.h"
 
class AActor;
class ALight;
class UCurveFloat;
class UHorrorLightComponent;

USTRUCT(BlueprintType)
struct HORROREVENT_API FHorrorLIghtStruct
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLightDelegate, UHorrorLightComponent*, EffectedLight);

UCLASS(ClassGroup = (Horror), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class HORROREVENT_API UHorrorLightComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = "Light", EditAnywhere, BlueprintReadWrite)
	bool IsBroke;
	
	UPROPERTY(Category = "Light", EditAnywhere, BlueprintReadWrite)
	bool IsOn;

	UPROPERTY(Category = "Lights", EditAnywhere, BlueprintReadWrite)
	float MultiflyIntensity = 1.0f;

	UPROPERTY(Category = "Lights", EditAnywhere, BlueprintReadWrite)
	FLinearColor BaseColor = FLinearColor::White;

	UPROPERTY(Category = "Lights", EditAnywhere, BlueprintReadWrite)
	TArray<FHorrorLIghtStruct> Lights;

public:
	FORCEINLINE bool IsItOn() const
	{
		return IsOn;
	}
	FORCEINLINE bool DoesItTurnOn(bool NewOn) const
	{
		return ((IsBroke == false) && NewOn);
	}
	FORCEINLINE bool DoesItShine() const
	{
		return (MultiflyIntensity) > 0.f && (BaseColor != BaseColor.Black);
	}

public:
	UFUNCTION(Category = "Horror", BlueprintCallable)
	void SetLgiht(bool NewOn);

	UFUNCTION(Category = "Horror", BlueprintCallable)
	void ToggleLight();

	UFUNCTION(Category = "Horror", BlueprintCallable, CallInEditor)
	void UpdateLight();
	
	UFUNCTION(Category = "Horror", BlueprintCallable, CallInEditor)
	void CatchLight();

	UPROPERTY(BlueprintAssignable)
	FLightDelegate LightOnDelegate;

	UPROPERTY(BlueprintAssignable)
	FLightDelegate LightOffDelegate;
};

/*
 * Switch light.
 */
UCLASS()
class HORROREVENT_API UHorrorEventInstance_LightSwitch : public UHorrorEventInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = "HorrorEvent", EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> HorrorLightActor;

public:
	virtual void CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired) override;
};