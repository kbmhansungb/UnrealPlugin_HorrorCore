// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/NoExportTypes.h"
#include "HorrorItemInterface.generated.h"

class AActor;

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
UINTERFACE(MinimalAPI)
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
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	FName GetItemName();
	virtual FName GetItemName_Implementation();;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	int32 GetItemMaxStack();
	virtual int32 GetItemMaxStack_Implementation();;

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	AActor* GetItemActor();
	virtual AActor* GetItemActor_Implementation();
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintImplementableEvent)
	FIntSize2D GetSizePoint();
	virtual FIntSize2D GetSizePoint_Implementation();
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