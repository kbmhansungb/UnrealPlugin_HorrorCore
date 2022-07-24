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


void FHorrorItemBundle::PutIn()
{
	Count += 1;
}

void FHorrorItemBundle::TakeOut()
{
	Count -= 1;
}

bool FHorrorItemBundle::IsEmpty() const
{
	return 0 == Count;
}

bool FHorrorItemBundle::CanTakeOut() const
{
	return Count > 0;
}

bool FHorrorItemBundle::CanPutIn() const
{
	return TypeInterface->GetItemMaxStack() > Count;
}