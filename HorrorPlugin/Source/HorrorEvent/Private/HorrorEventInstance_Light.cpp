// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventInstance_Light.h"
#include "Engine/Light.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"


void UHorrorLightComponent::SetState(bool NewOn)
{
	IsOn = DoesItTurnOn(NewOn);
	UpdateLight();
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

AHorrorLight::AHorrorLight()
{
	HorrorLightComponent = CreateDefaultSubobject<UHorrorLightComponent>(FName("HorrorLIghtComponent"));
}

void AHorrorLight::BeginPlay()
{
	Super::BeginPlay();

	SetLight_Implementation(HorrorLightComponent->IsOn);
}

void AHorrorLight::SetLight_Implementation(bool NewOn)
{
	HorrorLightComponent->SetState(NewOn);

	PostSetLightState();
}

void AHorrorLight::SwitchLight_Implementation()
{
	SetLight_Implementation(!HorrorLightComponent->IsOn);
}

void UHorrorEventInstance_LightSwitch::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	IHorrorLightInterface::Execute_SwitchLight(HorrorLightActor.GetObject());
}
