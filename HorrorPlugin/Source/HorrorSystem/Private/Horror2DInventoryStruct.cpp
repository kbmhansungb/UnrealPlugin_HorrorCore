#include "Horror2DInventoryStruct.h"


FHorrorItem2DInventoryData::FHorrorItem2DInventoryData(const FHorrorItemBundle& ItemStack, const FIntPoint& StartIndex)
	: ItemStack(ItemStack), StartIndex(StartIndex) {}

bool FHorrorItem2DInventoryData::IsIntersect(const FIntPoint& Int) const
{
	const FIntSize2D& Size = ItemStack.TypeInterface->GetIconSize();

	const bool& InX = (StartIndex.X <= Int.X) && (Int.X <= StartIndex.X + Size.X);
	const bool& InY = (StartIndex.Y <= Int.Y) && (Int.Y <= StartIndex.Y + Size.Y);

	return InX && InY;
}

bool FHorrorItem2DInventoryData::IsEqualItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	return Iteminterface == ItemStack.TypeInterface;
}

bool FHorror2DInventoryStruct::IsValidIndex(const FIntPoint& Index) const
{
	return
		InventorySize.X > Index.X && Index.X >= 0 &&
		InventorySize.Y > Index.Y && Index.Y >= 0;
}

bool FHorror2DInventoryStruct::IsNotExceed(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	const FIntPoint& MaxPoint = Index + Iteminterface->GetIconSize();

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

	const FHorrorItem2DInventoryData* ItemStack = GetItemStackPtr(Index);

	if (ItemStack)
	{
		if (ItemStack->IsEqualItem(Iteminterface))
		{
			return ItemStack->ItemStack.CanPutIn();
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

void FHorror2DInventoryStruct::StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index)
{
	FHorrorItem2DInventoryData* ItemStack = GetItemStackPtr(Index);

	if (!ItemStack)
	{
		const int32& ElumIndex = Items.Add(FHorrorItem2DInventoryData(FHorrorItemBundle(Iteminterface, 1), Index));
		ItemStack = &Items[ElumIndex];
	}
	else
	{
		ItemStack->ItemStack.PutIn();
	}
}

bool FHorror2DInventoryStruct::IsTakable(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	if (IsValidIndex(Index) == false)
	{
		return false;
	}

	const FHorrorItem2DInventoryData* ItemStack = GetItemStackPtr(Index);

	if (!ItemStack)
	{
		return false;
	}

	return ItemStack->ItemStack.CanTakeOut();
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

void FHorror2DInventoryStruct::TakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& ItemType)
{
	FHorrorItem2DInventoryData* ItemStack = GetItemStackPtr(Index);

	ItemStack->ItemStack.TakeOut();

	if (ItemStack->ItemStack.IsEmpty())
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
		if (IsNotExceed(Item.StartIndex, Item.ItemStack.TypeInterface) == false)
		{
			OutItemStacks.Add(Item.ItemStack);

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
