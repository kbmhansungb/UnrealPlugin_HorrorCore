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

// 유효하면 아이템으로 스폰될 수 있고 그렇지 않으면 스폰될 수 없습니다

