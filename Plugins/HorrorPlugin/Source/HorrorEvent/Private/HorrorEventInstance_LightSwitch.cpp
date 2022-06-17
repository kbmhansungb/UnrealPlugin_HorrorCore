// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventInstance_LightSwitch.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"


void UHorrorEventInstance_LightSwitch::CallHorrorEvent_Implementation(const FHorrorEventStruct& HorrorEventRequired)
{
	UpdateState();
}

void UHorrorEventInstance_LightSwitch::UpdateState()
{	
	if (Actor.IsValid() == false)
	{
		return;
	}

	bool NewLightVisibility = IsLightEffectTheWorld();
	UpdateComponentsLight(Actor.Get(), NewLightVisibility);
	UpdateChildActorsLight(Actor.Get(), NewLightVisibility);
}

void UHorrorEventInstance_LightSwitch::UpdateComponentsLight(AActor* TargetActor, bool Visibility)
{
	TArray<UActorComponent*> ChildComponents = TargetActor->GetComponentsByClass(ULocalLightComponent::StaticClass());
	for (UActorComponent* ChildComponent : ChildComponents)
	{
		ULocalLightComponent* LocalLight = Cast<ULocalLightComponent>(ChildComponent);

		UpdateLocalLightComponent(LocalLight, Visibility);
	}
}

void UHorrorEventInstance_LightSwitch::UpdateChildActorsLight(AActor* TargetActor, bool Visibility)
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

void UHorrorEventInstance_LightSwitch::UpdateLocalLightComponent(ULocalLightComponent* LocalLightComponent, bool Visibility)
{
	//LocalLightComponent->bAffectsWorld;
	LocalLightComponent->SetVisibility(Visibility);
}

bool UHorrorEventInstance_LightSwitch::IsLightEffectTheWorld()
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
