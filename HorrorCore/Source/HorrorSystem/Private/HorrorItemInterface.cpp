// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorItemInterface.h"
#include "Kismet/GameplayStatics.h"

AActor* IHorrorItemInterface::SpawnItemActor(AActor* ContextObject, const FTransform& Transform, bool bNoCollisionFail, AActor* Owner) const
{
	const TSubclassOf<AActor>& ActorClass = GetItemActorClass();
	if (!ActorClass.Get())
	{
		return nullptr;
	}

	return UGameplayStatics::BeginSpawningActorFromClass(ContextObject, ActorClass, Transform, bNoCollisionFail, Owner);
}