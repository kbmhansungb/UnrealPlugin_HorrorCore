// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorItemInterface.h"
#include "Horror2DInventoryStruct.generated.h"

USTRUCT(BlueprintType)
struct FHorrorItem2DInventoryData
{
	GENERATED_BODY()

public:
	FHorrorItem2DInventoryData() = default;
	FHorrorItem2DInventoryData(const FHorrorItemBundle& ItemBundle, const FIntPoint& StartIndex)
		: ItemBundle(ItemBundle), StartIndex(StartIndex) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHorrorItemBundle ItemBundle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	FIntPoint StartIndex;

public:
	inline bool IsIntersect(const FIntPoint& Int) const;
	inline bool IsEqualItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
};

inline bool FHorrorItem2DInventoryData::IsIntersect(const FIntPoint& Int) const
{
	const FIntSize2D& Size = ItemBundle.TypeInterface->GetIconSize();

	const bool& InX = (StartIndex.X <= Int.X) && (Int.X <= StartIndex.X + Size.X);
	const bool& InY = (StartIndex.Y <= Int.Y) && (Int.Y <= StartIndex.Y + Size.Y);

	return InX && InY;
}

inline bool FHorrorItem2DInventoryData::IsEqualItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	return Iteminterface == ItemBundle.TypeInterface;
}

USTRUCT(BlueprintType)
struct FHorror2DInventoryStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHorrorItem2DInventoryData> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	FIntSize2D InventorySize;

public:
	inline bool IsValidIndex(const FIntPoint& Index) const;
	inline bool IsNotExceed(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
	inline FHorrorItem2DInventoryData* GetItemStackPtr(const FIntPoint& Index);
	inline const FHorrorItem2DInventoryData* GetItemStackPtr(const FIntPoint& Index) const;
	inline int32 GetItemStackIndex(const FIntPoint& Index) const;

public:
	inline bool IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index) const;
	inline bool TryStoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index);
private:
	inline void StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index);

public:
	inline bool IsTakable(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
	inline bool TryTakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface);
private:
	inline void TakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& ItemType);

public:
	inline void TrySetSize(const FIntSize2D& NewSize, TArray<FHorrorItemBundle>& OutItemStacks);
	inline void OutInvalidItems(TArray<FHorrorItemBundle>& OutItemStacks);
private:
	inline void SetSize(const FIntSize2D& NewSize);
};

inline bool FHorror2DInventoryStruct::IsValidIndex(const FIntPoint& Index) const
{
	return
		InventorySize.X > Index.X && Index.X >= 0 &&
		InventorySize.Y > Index.Y && Index.Y >= 0;
}

inline bool FHorror2DInventoryStruct::IsNotExceed(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& Iteminterface) const
{
	const FIntPoint& MaxPoint = Index + Iteminterface->GetIconSize();

	return
		InventorySize.X >= MaxPoint.X &&
		InventorySize.Y >= MaxPoint.Y;
}

inline FHorrorItem2DInventoryData* FHorror2DInventoryStruct::GetItemStackPtr(const FIntPoint& Index)
{
	return Items.FindByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

inline const FHorrorItem2DInventoryData* FHorror2DInventoryStruct::GetItemStackPtr(const FIntPoint& Index) const
{
	return Items.FindByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

inline int32 FHorror2DInventoryStruct::GetItemStackIndex(const FIntPoint& Index) const
{
	return Items.IndexOfByPredicate(
		[&](const FHorrorItem2DInventoryData& Elum)
		{
			return true == Elum.IsIntersect(Index);
		});
}

inline bool FHorror2DInventoryStruct::IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index) const
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

inline bool FHorror2DInventoryStruct::TryStoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index)
{
	if (IsStorable(Iteminterface, Index) == false)
	{
		return false;
	}

	StoreItem(Iteminterface, Index);

	return true;
}

inline void FHorror2DInventoryStruct::StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index)
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

inline bool FHorror2DInventoryStruct::IsTakable(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const
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

inline bool FHorror2DInventoryStruct::TryTakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface)
{
	if (IsTakable(Index, Iteminterface) == false)
	{
		return false;
	}

	TakeItem(Index, Iteminterface);

	return true;
}

inline void FHorror2DInventoryStruct::TakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& ItemType)
{
	FHorrorItem2DInventoryData* ItemBundle = GetItemStackPtr(Index);

	ItemType = ItemBundle->ItemBundle.TypeInterface;
	ItemBundle->ItemBundle.TakeOut();

	if (ItemBundle->ItemBundle.IsEmpty())
	{
		Items.RemoveAt(GetItemStackIndex(Index));
	}
}

inline void FHorror2DInventoryStruct::TrySetSize(const FIntSize2D& NewSize, TArray<FHorrorItemBundle>& OutItemStacks)
{
	SetSize(NewSize);
	OutInvalidItems(OutItemStacks);
}

inline void FHorror2DInventoryStruct::OutInvalidItems(TArray<FHorrorItemBundle>& OutItemStacks)
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

inline void FHorror2DInventoryStruct::SetSize(const FIntSize2D& NewSize)
{
	InventorySize = NewSize;
}

