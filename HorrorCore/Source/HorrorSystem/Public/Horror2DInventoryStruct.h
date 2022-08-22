// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorItemInterface.h"
#include "HorrorItemActorInterface.h"
#include "Engine/World.h"
#include "Horror2DInventoryStruct.generated.h"

USTRUCT(BlueprintType)
struct HORRORSYSTEM_API FHorrorItem2DInventoryData
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
	bool IsIntersect(const FIntPoint& Int) const;
	bool IsIntersect(const FIntPoint& Index, const FIntSize2D& Size2D) const;
	bool IsEqualItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
};

USTRUCT(BlueprintType)
struct HORRORSYSTEM_API FHorror2DInventoryStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHorrorItem2DInventoryData> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	FIntSize2D InventorySize;

public:
	bool IsValidIndex(const FIntPoint& Index) const;
	bool IsNotExceed(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& ItemInterface) const;
	bool IsOverlaped(const FIntPoint& Index, const TScriptInterface<IHorrorItemInterface>& ItemInterface) const;
	FHorrorItem2DInventoryData* GetItemStackPtr(const FIntPoint& Index);
	const FHorrorItem2DInventoryData* GetItemStackPtr(const FIntPoint& Index) const;
	int32 GetItemStackIndex(const FIntPoint& Index) const;

public:
	bool IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index) const;
	bool TryStoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index);
	bool TryStoreItemActor(const TScriptInterface<IHorrorItemActorInterface>& ItemActorInterface, const FIntPoint& Index);
private:
	void StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, const FIntPoint& Index);

public:
	bool IsTakable(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const;
	bool TryTakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& Iteminterface);
	bool TryTakeItemActor(UObject* Outer, const FTransform& Transform, const FIntPoint& Index, TScriptInterface<IHorrorItemActorInterface>& ItemActorInterface);
private:
	void TakeItem(const FIntPoint& Index, TScriptInterface<IHorrorItemInterface>& ItemType);

public:
	void TrySetSize(const FIntSize2D& NewSize, TArray<FHorrorItemBundle>& OutItemStacks);
	void OutInvalidItems(TArray<FHorrorItemBundle>& OutItemStacks);
private:
	void SetSize(const FIntSize2D& NewSize);
};