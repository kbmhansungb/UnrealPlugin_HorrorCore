// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorEventStruct.h"

FHorrorEventStruct::FHorrorEventStruct(AActor* Subject, AActor* Object, TScriptInterface<IHorrorItemInterface> ItemInterface, FVector Origin, FVector Direction)
	: Subject(Subject), Object(Object), ItemInterface(ItemInterface), Origin(Origin), Direction(Direction)
{
}
