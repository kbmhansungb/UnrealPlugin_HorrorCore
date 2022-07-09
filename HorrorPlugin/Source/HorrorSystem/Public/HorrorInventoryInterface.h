// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorItemInterface.h"
#include "HorrorInventoryInterface.generated.h"

USTRUCT(BlueprintType)
struct FInventoryRowData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> ItemIndex;
};

USTRUCT(BlueprintType)
struct FInventoryStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHorrorItemStruct> Items;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryRowData> Data;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UHorrorInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORSYSTEM_API IHorrorInventoryInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	bool IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const;
	virtual bool IsStorable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const { return false; }
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index);
	virtual void StoreItem_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) {}
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	bool IsTakable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const;
	virtual bool IsTakable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const { return false; }

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IHorrorItemInterface> TakeItem(FIntPoint Index);
	virtual TScriptInterface<IHorrorItemInterface> TakeItem_Implementation(FIntPoint Index) { return TScriptInterface<IHorrorItemInterface>(); }

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IHorrorItemInterface> GetHoldItem() const;
	virtual TScriptInterface<IHorrorItemInterface> GetHoldItem_Implementation() const { return TScriptInterface<IHorrorItemInterface>(); }

public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	FIntSize2D GetInventorySize() const;
	virtual FIntSize2D GetInventorySize_Implementation() const { return FIntSize2D(); }
};
