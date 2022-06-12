// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventCondition_HaveHorrorItem.h"
#include "HorrorEventCallerComponent.h"
#include "GameFramework/Actor.h"

bool UHorrorEventCondition_HaveHorrorItem::CheckCondition_Implementation(const FHorrorEventRequired& Required)
{
	if (!Required.ItemInterface.GetObject())
	{
		return false;
	}

	if (CompareClass)
	{
		if (CompareClass != Required.ItemInterface.GetObject()->GetClass())
		{
			return false;
		}
	}

	if (SpecificObject)
	{
		if (SpecificObject != Required.ItemInterface.GetObject())
		{
			return false;
		}
	}

	return true;
}
