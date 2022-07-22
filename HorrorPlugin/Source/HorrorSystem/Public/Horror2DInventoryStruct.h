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
	FHorrorItem2DInventoryData(const FHorrorItemStack& ItemStack, const FIntPoint& StartIndex)
		: ItemStack(ItemStack), StartIndex(StartIndex) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHorrorItemStack ItemStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	FIntPoint StartIndex;

public:
	bool IsIntersect(const FIntPoint& Int) const;
	bool IsEqualItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
};

USTRUCT(BlueprintType)
struct F2DInventoryStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHorrorItem2DInventoryData> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	FIntSize2D InventorySize;

public:
	bool IsValidIndex(const FIntPoint& Index) const;
	bool IsNotExceed(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
	FHorrorItem2DInventoryData* GetItemStackPtr(const FIntPoint& Index);
	const FHorrorItem2DInventoryData* GetItemStackPtr(const FIntPoint& Index) const;
	int32 GetItemStackIndex(const FIntPoint& Index) const;

public:
	bool IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index) const;
	bool TryStoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index);
private:
	void StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index);

public:
	bool IsTakable(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
	bool TryTakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface);
private:
	void TakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& ItemType);

public:
	// bool IsValidInventory();
	// bool IsOutOfRange();
	// bool IsStackValid();
};