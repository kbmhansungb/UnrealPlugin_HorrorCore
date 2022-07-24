// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HorrorItem.h"
#include "Horror2DInventoryStruct.h"
#include "Horror2DInventoryStructTest.generated.h"


UENUM(BlueprintType)
enum class EACTION : uint8
{
	NONE,
	STORE,
	TAKE,
};

USTRUCT(BlueprintType)
struct FWorkUnit
{
	GENERATED_BODY()

public:
	// 저장할 때는, 저장하는 아이템을, 꺼낼때는 기대하는 아이템을 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHorrorItem* HorrorItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EACTION Action;
};

USTRUCT(BlueprintType)
struct FHorrorInventory2DInsertTest : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHorror2DInventoryStruct InventoryInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWorkUnit> WorkUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Desire;
};