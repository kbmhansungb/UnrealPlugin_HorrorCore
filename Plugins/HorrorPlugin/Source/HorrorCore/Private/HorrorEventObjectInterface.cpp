// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventObjectInterface.h"

// Add default functionality here for any IHorrorEventObjectInterface functions that are not pure virtual.

bool IHorrorEventObjectInterface::isLocalEvent_Implementation(const FHorrorEventStruct& Required)
{
	return false;
}

bool IHorrorEventObjectInterface::IsExecuteable_Implementation(const FHorrorEventStruct& Required)
{
	return true; 
}

void IHorrorEventObjectInterface::CallHorrorEvent_Implementation(const FHorrorEventStruct& Required) 
{ 
}
