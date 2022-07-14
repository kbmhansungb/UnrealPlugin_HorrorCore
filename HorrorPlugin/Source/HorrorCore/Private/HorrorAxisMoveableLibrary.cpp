// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorAxisMoveableLibrary.h"
#include "Components/SceneComponent.h"
#include "HorrorAxisMoveableInterface.h"

void UHorrorAxisMoveableLibrary::InputAxisMovement(USceneComponent* Component, const FVector2D& MouseMovement, bool MeetMoveableInterface)
{
	TArray<TScriptInterface<IHorrorAxisMoveableInterface>> MoveableInterfaces;
	USceneComponent* Target;
	SearchMovealbeInterfaces(Component, MeetMoveableInterface, MoveableInterfaces, Target);

	for (const TScriptInterface<IHorrorAxisMoveableInterface>& MoveableInterface : MoveableInterfaces)
	{
		InputAxisMovementTo(MoveableInterface, Target, MouseMovement);
	}
}

void UHorrorAxisMoveableLibrary::SearchMovealbeInterfaces(USceneComponent* Component, bool MeetMoveableInterface, TArray<TScriptInterface<IHorrorAxisMoveableInterface>>& MoveableInterfaces, USceneComponent*& SceneComponent)
{
	MoveableInterfaces.Empty();
	SceneComponent = Component;

	if (MeetMoveableInterface == false)
	{
		if (Component->GetClass()->ImplementsInterface(UHorrorAxisMoveableInterface::StaticClass()))
		{
			MoveableInterfaces.Add(Component);
		}
	}
	else
	{
		USceneComponent* ComponentIterator = Component->GetAttachParent();

		bool HadMet = false;
		while (ComponentIterator)
		{
			bool IsInterface = ComponentIterator->GetClass()->ImplementsInterface(UHorrorAxisMoveableInterface::StaticClass());
			if (IsInterface)
			{
				MoveableInterfaces.Add(ComponentIterator);

				HadMet = true;
			}

			if (!IsInterface && HadMet)
			{
				return;
			}

			if (!HadMet)
			{
				SceneComponent = ComponentIterator;
			}

			ComponentIterator = ComponentIterator->GetAttachParent();
		}
	}
}

void UHorrorAxisMoveableLibrary::InputAxisMovementTo(const TScriptInterface<IHorrorAxisMoveableInterface>& MoveableInterfaces, USceneComponent* SceneComponent, const FVector2D& MouseMovement)
{
	IHorrorAxisMoveableInterface::Execute_ApplyAxisMovealbe(MoveableInterfaces.GetObject(), SceneComponent, MouseMovement);
}
