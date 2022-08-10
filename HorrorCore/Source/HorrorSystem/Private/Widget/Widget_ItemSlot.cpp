// 2022 06    Bum moo, Kim    Free copyright


#include "Widget_ItemSlot.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/Pawn.h>
#include <HorrorHandComponent.h>
#include <HorrorItemInterface.h>
#include <HorrorItemActorInterface.h>

TScriptInterface<IHorrorItemActorInterface> UWidget_ItemSlot::GetItemInterface_Implementation(bool& IsHold) const
{
	UHorrorHandComponent* HandComponent = Cast<UHorrorHandComponent>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn()->GetComponentByClass(UHorrorHandComponent::StaticClass()));
	
	IsHold = false;

	if (HandComponent)
	{
		const TScriptInterface<IHorrorHoldableInterface>& Holdable = UHorrorHandComponent::Execute_GetHoldable(HandComponent);
		if (Holdable.GetObject())
		{
			IsHold = true;

			if (Holdable.GetObject()->GetClass()->ImplementsInterface(UHorrorItemActorInterface::StaticClass()))
			{
				return Holdable.GetObject();
			}
		}
	}

	return TScriptInterface<IHorrorItemActorInterface>();
}
