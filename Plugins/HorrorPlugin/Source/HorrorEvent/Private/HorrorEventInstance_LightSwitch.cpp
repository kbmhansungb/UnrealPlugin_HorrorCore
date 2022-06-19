// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventInstance_LightSwitch.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"

void UHorrorLight_Default::UpdateState()
{
	bool NewLightVisibility = IsLightEffectTheWorld();
	UpdateComponentsLight(GetOwner(), NewLightVisibility);
	UpdateChildActorsLight(GetOwner(), NewLightVisibility);
}

void UHorrorLight_Default::UpdateComponentsLight(AActor* TargetActor, bool Visibility)
{
	TArray<ULocalLightComponent*> LocalLights;
	TargetActor->GetComponents<ULocalLightComponent>(LocalLights);
	for (ULocalLightComponent* LocalLight : LocalLights)
	{
		UpdateLocalLightComponent(LocalLight, Visibility);
	}
}

void UHorrorLight_Default::UpdateChildActorsLight(AActor* TargetActor, bool Visibility)
{
	TArray<AActor*> ChildActors;
	TargetActor->GetAttachedActors(ChildActors);

	for (AActor* ChildActor : ChildActors)
	{
		ULocalLightComponent* LocalLight = Cast<ULocalLightComponent>(ChildActor->GetRootComponent());

		if (LocalLight != nullptr)
		{
			UpdateLocalLightComponent(LocalLight, Visibility);
		}
	}
}

void UHorrorLight_Default::UpdateLocalLightComponent(ULocalLightComponent* LocalLightComponent, bool Visibility)
{
	//LocalLightComponent->bAffectsWorld;
	LocalLightComponent->SetVisibility(Visibility);
}

bool UHorrorLight_Default::IsLightEffectTheWorld()
{
	switch (LightState)
	{
	case ELightState::OFF:
	case ELightState::BROKE:
		return false;
	case ELightState::ON:
	case ELightState::UNSTABLE:
		return true;
	default:
		check(false && "Add a case.");
		return false;
	}
}

void UHorrorEventInstance_LightSwitch::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	if (HorrorLightActor.IsValid())
	{
		UHorrorLight_Default* HorrorLight = Cast<UHorrorLight_Default>(HorrorLightActor.Get()->GetComponentByClass(UHorrorLight_Default::StaticClass()));
		if (HorrorLight)
		{
			HorrorLight->UpdateState();
		}
	}
}
