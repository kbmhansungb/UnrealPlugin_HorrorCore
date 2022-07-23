// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorItemInterface.h"

// Add default functionality here for any IHorrorItemInterface functions that are not pure virtual.

FName IHorrorItemInterface::GetItemName_Implementation() const { return FName(); }

int32 IHorrorItemInterface::GetItemMaxStack_Implementation() const { return 0; }

TSubclassOf<AActor> IHorrorItemInterface::GetItemActor_Implementation() const { return TSubclassOf<AActor>(); }

FIntSize2D IHorrorItemInterface::GetSize_Implementation() const { return FIntSize2D(1, 1); }

FSlateBrush IHorrorItemInterface::GetIconBrush_Implementation() const { return FSlateBrush(); }

