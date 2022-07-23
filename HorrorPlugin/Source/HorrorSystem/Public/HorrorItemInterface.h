// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Styling/SlateBrush.h"
#include "HorrorHoldableInterface.h"
#include "HorrorItemInterface.generated.h"

USTRUCT(BlueprintType)
struct FIntSize2D
{
	GENERATED_BODY()

public:
	FIntSize2D() {};
	FIntSize2D(const int32 X, const int32 Y) : X(X), Y(Y) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;

public:
	FORCEINLINE bool operator == (const FIntSize2D& Other) const
	{
		return (X == Other.X) && (Y == Other.Y);
	}

	FORCEINLINE bool operator != (const FIntSize2D& Other) const
	{
		return (X != Other.X) || (Y != Other.Y);
	}
};

FORCEINLINE FIntPoint operator+(const FIntPoint& Point, const FIntSize2D& Size)
{
	return FIntPoint(Point.X + Size.X, Point.Y + Size.Y);
}

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UHorrorItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORSYSTEM_API IHorrorItemInterface
{
	GENERATED_BODY()

public:
	virtual AActor* SpawnItemActor(AActor* ContextObject, const FTransform& Transform, bool bNoCollisionFail = false, AActor* Owner = nullptr) const;

public:
	virtual const FName& GetItemName() const = 0;
	virtual int32 GetItemMaxStack() const = 0;

	// 유효하면 아이템으로 스폰될 수 있는 아이템이고 그렇지 않으면 스폰될 수 없는 아이템입니다.
	virtual const TSubclassOf<AActor>& GetItemActorClass() const = 0;

	virtual const FIntSize2D& GetIconSize() const = 0;
	virtual const FSlateBrush& GetIconBrush() const = 0;
};


/**
 *
 */
USTRUCT(BlueprintType)
struct FHorrorItemBundle
{
	GENERATED_BODY()

public:
	FHorrorItemBundle() = default;
	FHorrorItemBundle(const TScriptInterface<IHorrorItemInterface>& TypeInterface, int32 Count)
		: TypeInterface(TypeInterface), Count(Count) 
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<IHorrorItemInterface> TypeInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	int32 Count;

public:
	void PutIn();
	void TakeOut();
	bool IsEmpty() const;
	bool CanTakeOut() const;
	bool CanPutIn() const;
};