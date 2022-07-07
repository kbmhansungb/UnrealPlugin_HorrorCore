// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorItemInterface.h"

// Add default functionality here for any IHorrorItemInterface functions that are not pure virtual.

FName IHorrorItemInterface::GetItemName_Implementation() { return FName(); }

int32 IHorrorItemInterface::GetItemMaxStack_Implementation() { return 0; }

AActor* IHorrorItemInterface::GetItemActor_Implementation() { return nullptr; }

FIntSize2D IHorrorItemInterface::GetSizePoint_Implementation() { return FIntSize2D(1, 1); }
