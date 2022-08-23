// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventInstance_Light.h"
#include "Engine/Light.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

void UHorrorLightComponent::SetLgiht(bool NewOn)
{
	IsOn = DoesItTurnOn(NewOn);
	UpdateLight();

	if (IsItUnstable())
	{
		TArray<UActorComponent*> Components = GetOwner()->GetComponentsByTag(UActorSequenceComponent::StaticClass(), UnstableSequenceTag);
		for (UActorComponent* Component : Components)
		{
			UActorSequenceComponent* SequenceComponent = Cast<UActorSequenceComponent>(Component);
			SequenceComponent->GetSequencePlayer()->Play();
		}
	}
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

	if (IsOn)
	{
		if (LightOnDelegate.IsBound())
		{
			LightOnDelegate.Broadcast(this);
		}
	}
	else
	{
		if (LightOffDelegate.IsBound())
		{
			LightOffDelegate.Broadcast(this);
		}
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
