// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorItem.h"

void UHorrorItem::GetItemName_Implementation(FName& ItemName) const
{
	ItemName = Name;
}

int32 UHorrorItem::GetItemMaxStack_Implementation() const
{
	return StackSize;
}

void UHorrorItem::GetItemActorClass_Implementation(TSubclassOf<AActor>& ItemActorClass) const
{
	ItemActorClass = ActorClass;
}

void UHorrorItem::GetIconSize_Implementation(FIntSize2D& ItemIntSize) const
{
	ItemIntSize = Size;
}

void UHorrorItem::GetIconBrush_Implementation(FSlateBrush& ItemIcon) const
{
	ItemIcon = IconBrush;
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
	return IHorrorItemInterface::Execute_GetItemMaxStack(TypeInterface.GetObject()) > Count;
}