// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HorrorItemInterface.h"
#include "HorrorItem.generated.h"

class AActor;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UHorrorItem : public UPrimaryDataAsset
	, public IHorrorItemInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntSize2D Size = FIntSize2D(1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush IconBrush;

public:
	virtual FName GetItemName_Implementation() const override;
	virtual int32 GetItemMaxStack_Implementation() const override;
	virtual TSubclassOf<AActor> GetItemActor_Implementation() const override;
	virtual FIntSize2D GetSize_Implementation() const override;
	virtual FSlateBrush GetIconBrush_Implementation() const override;
};