// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorItemInterface.h"
#include "Kismet/GameplayStatics.h"

bool FIntSize2D::operator == (const FIntSize2D& Other) const
{
	return (X == Other.X) && (Y == Other.Y);
}

bool FIntSize2D::operator != (const FIntSize2D& Other) const
{
	return (X != Other.X) || (Y != Other.Y);
}

FIntPoint operator+(const FIntPoint& Point, const FIntSize2D& Size)
{
	return FIntPoint(Point.X + Size.X, Point.Y + Size.Y);
}


AActor* IHorrorItemInterface::SpawnItemActor(AActor* ContextObject, const FTransform& Transform, bool bNoCollisionFail, AActor* Owner) const
{
	TSubclassOf<AActor> ActorClass;
	GetItemActorClass(ActorClass);
	if (!ActorClass.Get())
	{
		return nullptr;
	}

	return UGameplayStatics::BeginSpawningActorFromClass(ContextObject, ActorClass, Transform, bNoCollisionFail, Owner);
}