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
	FString TestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHorror2DInventoryStruct InventoryInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWorkUnit> WorkUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Desire;
};