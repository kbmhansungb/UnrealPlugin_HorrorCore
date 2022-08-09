#include "Horror2DInventoryStruct.h"

bool FHorrorItem2DInventoryData::IsIntersect(const FIntPoint& Int) const
{
	FIntSize2D GetIconSize;
	IHorrorItemInterface::Execute_GetIconSize(ItemBundle.TypeInterface.GetObject(), GetIconSize);

	const bool& InX = (StartIndex.X <= Int.X) && (Int.X <= StartIndex.X + GetIconSize.X);
	const bool& InY = (StartIndex.Y <= Int.Y) && (Int.Y <= StartIndex.Y + GetIconSize.Y);

	return InX && InY;
}

bool FHorrorItem2DInventoryData::IsEqualItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	return Iteminterface == ItemBundle.TypeInterface;
}


bool FHorror2DInventoryStruct::IsValidIndex(const FIntPoint& Index) const
{
	return
		InventorySize.X > Index.X && Index.X >= 0 &&
		InventorySize.Y > Index.Y && Index.Y >= 0;
}

bool FHorror2DInventoryStruct::IsNotExceed(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	FIntSize2D IconSize;
	IHorrorItemInterface::Execute_GetIconSize(Iteminterface.GetObject(), IconSize);

	const FIntPoint& MaxPoint = Index + IconSize;

	return
		InventorySize.X >= MaxPoint.X &&
		InventorySize.Y >= MaxPoint.Y;
}

FHorrorItem2DInventoryData* FHorror2DInventoryStruct::GetItemStackPtr(const FIntPoint& Index)
{
	return Items.FindByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

const FHorrorItem2DInventoryData* FHorror2DInventoryStruct::GetItemStackPtr(const FIntPoint& Index) const
{
	return Items.FindByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

int32 FHorror2DInventoryStruct::GetItemStackIndex(const FIntPoint& Index) const
{
	return Items.IndexOfByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

bool FHorror2DInventoryStruct::IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index) const
{
	if (IsValidIndex(Index) == false)
	{
		return false;
	}

	const FHorrorItem2DInventoryData* ItemData = GetItemStackPtr(Index);

	if (ItemData)
	{
		if (ItemData->IsEqualItem(Iteminterface))
		{
			return ItemData->ItemBundle.CanPutIn();
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!IsNotExceed(Index, Iteminterface))
		{
			return false;
		}
	}

	return true;
}

bool FHorror2DInventoryStruct::TryStoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index)
{
	if (IsStorable(Iteminterface, Index) == false)
	{
		return false;
	}

	StoreItem(Iteminterface, Index);

	return true;
}

bool FHorror2DInventoryStruct::TryStoreItemActor(const TScriptInterface<IHorrorItemActorInterface>& ItemActorInterface, const FIntPoint& Index)
{
	bool Result = TryStoreItem(IHorrorItemActorInterface::Execute_GetItemInterface(ItemActorInterface.GetObject()), Index);

	if (Result)
	{
		if (AActor* Actor = Cast<AActor>(ItemActorInterface.GetObject()))
		{
			Actor->Destroy();
		}
	}

	return Result;
}

void FHorror2DInventoryStruct::StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index)
{
	FHorrorItem2DInventoryData* ItemBundle = GetItemStackPtr(Index);

	if (!ItemBundle)
	{
		const int32& ElumIndex = Items.Add(FHorrorItem2DInventoryData(FHorrorItemBundle(Iteminterface, 1), Index));
		ItemBundle = &Items[ElumIndex];
	}
	else
	{
		ItemBundle->ItemBundle.PutIn();
	}
}

bool FHorror2DInventoryStruct::IsTakable(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	if (IsValidIndex(Index) == false)
	{
		return false;
	}

	const FHorrorItem2DInventoryData* ItemBundle = GetItemStackPtr(Index);

	if (!ItemBundle)
	{
		return false;
	}

	return ItemBundle->ItemBundle.CanTakeOut();
}

bool FHorror2DInventoryStruct::TryTakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface)
{
	if (IsTakable(Index, Iteminterface) == false)
	{
		return false;
	}

	TakeItem(Index, Iteminterface);

	return true;
}

bool FHorror2DInventoryStruct::TryTakeItemActor(UObject* Outer, const FTransform& Transform, const FIntPoint& Index, TScriptInterface<IHorrorItemActorInterface>& ItemActorInterface)
{
	TScriptInterface<IHorrorItemInterface> ItemInterface;
	bool Result = TryTakeItem(Index, ItemInterface);

	if (!Result)
	{
		ItemActorInterface = TScriptInterface<IHorrorItemActorInterface>();
		return false;
	}

	TSubclassOf<AActor> ActorClass;
	IHorrorItemInterface::Execute_GetItemActorClass(ItemInterface.GetObject(), ActorClass);

	AActor* Actor = Outer->GetWorld()->SpawnActor(ActorClass, &Transform);
	if (!Actor)
	{
		return false;
	}

	ItemActorInterface = Actor;
	return true;
}

void FHorror2DInventoryStruct::TakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& ItemType)
{
	FHorrorItem2DInventoryData* ItemBundle = GetItemStackPtr(Index);

	ItemType = ItemBundle->ItemBundle.TypeInterface;
	ItemBundle->ItemBundle.TakeOut();

	if (ItemBundle->ItemBundle.IsEmpty())
	{
		Items.RemoveAt(GetItemStackIndex(Index));
	}
}

void FHorror2DInventoryStruct::TrySetSize(const FIntSize2D& NewSize, TArray<FHorrorItemBundle>& OutItemStacks)
{
	SetSize(NewSize);
	OutInvalidItems(OutItemStacks);
}

void FHorror2DInventoryStruct::OutInvalidItems(TArray<FHorrorItemBundle>& OutItemStacks)
{
	OutItemStacks.Empty();

	for (int i = 0; i < Items.Num();)
	{
		const auto& Item = Items[i];
		if (IsNotExceed(Item.StartIndex, Item.ItemBundle.TypeInterface) == false)
		{
			OutItemStacks.Add(Item.ItemBundle);

			Items.RemoveAt(i);
		}
		else
		{
			++i;
		}
	}
}

void FHorror2DInventoryStruct::SetSize(const FIntSize2D& NewSize)
{
	InventorySize = NewSize;
}

