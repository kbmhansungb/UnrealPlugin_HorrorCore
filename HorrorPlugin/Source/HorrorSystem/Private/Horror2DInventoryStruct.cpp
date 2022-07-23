#include "Horror2DInventoryStruct.h"


FHorrorItem2DInventoryData::FHorrorItem2DInventoryData(const FHorrorItemStack& ItemStack, const FIntPoint& StartIndex)
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

bool F2DInventoryStruct::IsValidIndex(const FIntPoint& Index) const
{
	return
		InventorySize.X > Index.X && Index.X >= 0 &&
		InventorySize.Y > Index.Y && Index.Y >= 0;
}

bool F2DInventoryStruct::IsNotExceed(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	const FIntPoint& MaxPoint = Index + Iteminterface->GetIconSize();

	return 
		InventorySize.X >= MaxPoint.X &&
		InventorySize.Y >= MaxPoint.Y;
}

FHorrorItem2DInventoryData* F2DInventoryStruct::GetItemStackPtr(const FIntPoint& Index)
{
	return Items.FindByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

const FHorrorItem2DInventoryData* F2DInventoryStruct::GetItemStackPtr(const FIntPoint& Index) const
{
	return Items.FindByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

int32 F2DInventoryStruct::GetItemStackIndex(const FIntPoint& Index) const
{
	return Items.IndexOfByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

bool F2DInventoryStruct::IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index) const
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

bool F2DInventoryStruct::TryStoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index)
{
	if (IsStorable(Iteminterface, Index) == false)
	{
		return false;
	}

	StoreItem(Iteminterface, Index);

	return true;
}

void F2DInventoryStruct::StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index)
{
	FHorrorItem2DInventoryData* ItemStack = GetItemStackPtr(Index);

	if (!ItemStack)
	{
		const int32& ElumIndex = Items.Add(FHorrorItem2DInventoryData(FHorrorItemStack(Iteminterface, 1), Index));
		ItemStack = &Items[ElumIndex];
	}
	else
	{
		ItemStack->ItemStack.PutIn();
	}
}

bool F2DInventoryStruct::IsTakable(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const
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

bool F2DInventoryStruct::TryTakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface)
{
	if (IsTakable(Index, Iteminterface) == false)
	{
		return false;
	}

	TakeItem(Index, Iteminterface);

	return true;
}

void F2DInventoryStruct::TakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& ItemType)
{
	FHorrorItem2DInventoryData* ItemStack = GetItemStackPtr(Index);

	ItemStack->ItemStack.TakeOut();

	if (ItemStack->ItemStack.IsEmpty())
	{
		Items.RemoveAt(GetItemStackIndex(Index));
	}
}

void F2DInventoryStruct::TrySetSize(const FIntSize2D& NewSize, TArray<FHorrorItemStack>& OutItemStacks)
{
	SetSize(NewSize);
	OutInvalidItems(OutItemStacks);
}

void F2DInventoryStruct::OutInvalidItems(TArray<FHorrorItemStack>& OutItemStacks)
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

void F2DInventoryStruct::SetSize(const FIntSize2D& NewSize)
{
	InventorySize = NewSize;
}

