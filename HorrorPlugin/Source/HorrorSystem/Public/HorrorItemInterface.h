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
};

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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	FName GetItemName() const;
	virtual FName GetItemName_Implementation() const;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	int32 GetItemMaxStack() const;
	virtual int32 GetItemMaxStack_Implementation() const;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	TSubclassOf<AActor> GetItemActor() const;
	virtual TSubclassOf<AActor> GetItemActor_Implementation() const;
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	FIntSize2D GetSize() const;
	virtual FIntSize2D GetSize_Implementation() const;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	FSlateBrush GetIconBrush() const;
	virtual FSlateBrush GetIconBrush_Implementation() const;
};


/**
 *
 */
USTRUCT(BlueprintType)
struct FHorrorItemStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<UHorrorItemInterface> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stack;
};