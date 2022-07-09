// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorItem.h"

FName UHorrorItem::GetItemName_Implementation() const { return Name; }

int32 UHorrorItem::GetItemMaxStack_Implementation() const { return StackSize; }

TSubclassOf<AActor> UHorrorItem::GetItemActor_Implementation() const { return ActorClass; }

FIntSize2D UHorrorItem::GetSize_Implementation() const { return Size; }

FSlateBrush UHorrorItem::GetIconBrush_Implementation() const { return IconBrush; }
