// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventInstance_Light.h"
#include "Engine/Light.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UHorrorLightComponent::BeginPlay()
{
	Super::BeginPlay();

	InitDestinationSettings();
}

void UHorrorLightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateToDestination(DeltaTime);
}

void UHorrorLightComponent::SetLgiht(bool NewOn)
{
	IsOn = DoesItTurnOn(NewOn);
	UpdateLight();
}

void UHorrorLightComponent::ToggleLight()
{
	SetLgiht(!IsItOn());
}

void UHorrorLightComponent::UpdateLight()
{
	for (const auto& Light : Lights)
	{
		ULightComponent* LightComponent = Light.Light->GetLightComponent();

		LightComponent->SetVisibility(IsOn);
		LightComponent->SetIntensity(MultiflyIntensity * Light.Intensity);
		LightComponent->SetLightColor(BaseColor * Light.Color);
	}
}

void UHorrorLightComponent::CatchLight()
{
	Lights.Empty();

	TArray<AActor*> Actors;
	GetOwner()->GetAttachedActors(Actors);

	for (const AActor* Actor : Actors)
	{
		if (const ALight* Light = Cast<ALight>(Actor))
		{
			FHorrorLIghtStruct LightStruct;

			LightStruct.Light = const_cast<ALight*>(Light);
			LightStruct.Intensity = Light->GetLightComponent()->Intensity;
			LightStruct.Color = Light->GetLightComponent()->LightColor;

			Lights.Add(LightStruct);
		}
	}
}

void UHorrorLightComponent::InitDestinationSettings()
{
	DestinationMultiflyIntensity = MultiflyIntensity;
	DestinationBaseColor = BaseColor;
}

void UHorrorLightComponent::UpdateToDestination(float Deleta)
{
	MultiflyIntensity = UKismetMathLibrary::FInterpTo(MultiflyIntensity, DestinationMultiflyIntensity, Deleta, MultiflyIntensityLerpSpeed);
	BaseColor = UKismetMathLibrary::CInterpTo(BaseColor, DestinationBaseColor, Deleta, BaseColorLerpSpeed);
}

void UHorrorLightComponent::UpdateLightColor(FLinearColor Color, float Time)
{
	if (Time < FLT_EPSILON)
	{
		BaseColorLerpSpeed = 1.0f / Time;
		DestinationBaseColor = Color;

		SetComponentTickEnabled(true);
	}
	UpdateLight();
}

void UHorrorLightComponent::UpdateLightIntensity(float Intensity, float Time)
{
	if (Time > FLT_EPSILON)
	{
		MultiflyIntensityLerpSpeed = 1.0f / Time;
		DestinationMultiflyIntensity = Intensity;

		SetComponentTickEnabled(true);
	}
	UpdateLight();
}

void UHorrorEventInstance_LightSwitch::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	if (!HorrorLightActor.IsValid())
	{
		return;
	}

	UHorrorLightComponent* LightComponent = Cast<UHorrorLightComponent>(HorrorLightActor->GetComponentByClass(UHorrorLightComponent::StaticClass()));

	if (!LightComponent)
	{
		return;
	}

	LightComponent->ToggleLight();
}
