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
struct HORRORSYSTEM_API FIntSize2D
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
	bool operator == (const FIntSize2D& Other) const;
	bool operator != (const FIntSize2D& Other) const;
};

FIntPoint operator+(const FIntPoint& Point, const FIntSize2D& Size);

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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetItemName(FName& ItemName) const;
	virtual void GetItemName_Implementation(FName& ItemName) const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetItemMaxStack() const;
	virtual int32 GetItemMaxStack_Implementation() const = 0;

	// 유효하면 아이템으로 스폰될 수 있는 아이템이고 그렇지 않으면 스폰될 수 없는 아이템입니다.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetItemActorClass(TSubclassOf<AActor>& ItemActorClass) const;
	virtual void GetItemActorClass_Implementation(TSubclassOf<AActor>& ItemActorClass) const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetIconSize(FIntSize2D& ItemIntSize) const;
	virtual void GetIconSize_Implementation(FIntSize2D& ItemIntSize) const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetIconBrush(FSlateBrush& ItemIcon) const;
	virtual void GetIconBrush_Implementation(FSlateBrush& ItemIcon) const = 0;
};


/**
 *
 */
USTRUCT(BlueprintType)
struct HORRORSYSTEM_API FHorrorItemBundle
{
	GENERATED_BODY()

public:
	FHorrorItemBundle() = default;
	FHorrorItemBundle(const TScriptInterface<IHorrorItemInterface>& TypeInterface, int32 Count)
		: TypeInterface(TypeInterface), Count(Count) {}

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