// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorItem.h"

FName UHorrorItem::GetItemName_Implementation() { return Name; }

int32 UHorrorItem::GetItemMaxStack_Implementation() { return StackSize; }

AActor* UHorrorItem::GetItemActor_Implementation() { return Actor; }
